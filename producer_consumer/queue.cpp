#include <iostream>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

//static expected_queue_size()


typedef struct queue_element {
    int key;
    int val;
}element_t;

class Queue;

//int registerQueue(void *callbackFunc) { return 1 };

//int update_size(int queueID);

class Queue {
    
    int size, num_elements;
    int myID;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    int head_idx, tail_idx;
    element_t *queue;    
    
    // NOTE: Assuming that only ONE thread calls to create the queue.
    // If multiple thread were to call, we would need a singleton,
    // basically make the constructor private and have a static function 
    // creating this object. I'm out of time to provide this right now
public:
    Queue(int initial_size) {
        //int myId = registerQueue(Queue::change_size); // provide function pointer for callback here
        pthread_mutex_init(&mtx, NULL);
        pthread_cond_init(&cond, NULL);
        queue = (element_t*)(malloc(sizeof(element_t)*initial_size));
        num_elements = 0;
	size = initial_size;
        head_idx = tail_idx = 0;        
    }
    
    // NOTE: Here, we might need protection against threads trying to access
    // the queue to either enqueue, dequeue, or change its size
    // we would wait need to set some type of "I'm dying" flag, which would
    // disallow any future enqueues, and wait for the queue to be drained.
    ~Queue() {
        //unregister();
        free(queue);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);
    }
    
    // polling
    
    // interrupt
    // only one thread at a time --> actually, many threads can call this at the same time now that it's thread safe
    int resize(int new_size) {
    
    	if (size == new_size) {
    		return 0; // noop
    	}
    
        // allocate memory for queue of new size - this should be done outside of the critical section as
        // memory allocation *may* be a blocking call, depending on the implementation
        element_t *new_queue = (element_t*)malloc(sizeof(element_t)*new_size);
        if (new_queue == NULL) {
            return -1; // out of memory - logging probably not a good idea if we're already out of memory
        }
    
        pthread_mutex_lock(&mtx);
        while (num_elements > new_size) {
             // wait for elements to be dequeued before reducing the size of the queue
             std::cout << "a" << std::endl;
             pthread_cond_wait(&cond, &mtx);
             std::cout << "b" << std::endl;
        }
        
        // copy all the elements from the old queue to the new queue
        int cur_idx = tail_idx;
        for (int i=0; i < num_elements; i++) {
            new_queue[i] = queue[cur_idx];
            cur_idx = (cur_idx + 1)%size; //needs to be modulo of the "old" size
        }
        assert(cur_idx == (tail_idx + num_elements)%size);
        
        // free the original queue memory
        free(queue);
        
        // update to the new queue
        queue = new_queue;
        head_idx = num_elements;
        tail_idx = 0;
        size = new_size;
        assert(num_elements <= size);
        
        pthread_mutex_unlock(&mtx);

	return 0;
    }
    
    int enqueue(int key, int val) {
        pthread_mutex_lock(&mtx);
        assert(num_elements <= size);
        while(num_elements == size) {
            pthread_cond_wait(&cond, &mtx);
        }
        
        //enqueue at head
        queue[head_idx].key = key;
        queue[head_idx].val = val;
        head_idx = (head_idx +1 )% size;
        num_elements++;
	if (tail_idx < head_idx) {	
        	assert(num_elements == head_idx - tail_idx);
	} else {
		assert(size - tail_idx + head_idx == num_elements);
	}
        assert(num_elements <= size);
	
	// wake up any sleeping consumers
	pthread_cond_broadcast(&cond);
        
        pthread_mutex_unlock(&mtx);

	return 0;
    }
    
    element_t* dequeue() {
    
        element_t* ret_element = (element_t*)malloc(sizeof(element_t));
        if (NULL == ret_element) {
            // out of memory - maybe assert here
            return NULL;
        }
        
        pthread_mutex_lock(&mtx);
        
        // dequeue from tail
        while (num_elements == 0) {
		pthread_cond_wait(&cond,&mtx);
	}
	ret_element->key = queue[tail_idx].key;
        ret_element->val = queue[tail_idx].val;
        num_elements--;
        tail_idx = (tail_idx +1 )% size;

	if (head_idx >= tail_idx) {
        	assert(num_elements == head_idx - tail_idx);
	} else {
		assert(num_elements == size - tail_idx + head_idx);
	}
        assert(num_elements >= 0);
        
        // NOTE: a possible optimization here would be to 
        // wake up producers only once X spaces are available in the queue.
        // This is to avoid lots of context switches between producer and
        // consumer. This is tuning.
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mtx);        
        
        return ret_element;
    }
    
};

static int INITIAL_QUEUE_SIZE = 10;
static Queue theQueue(INITIAL_QUEUE_SIZE);

static int NUM_TO_PRODUCE = 5000;
void * produce(void *arg0) 
{
	for (int i = 0; i < NUM_TO_PRODUCE; i++) {
		theQueue.enqueue(i, i);
		theQueue.resize(NUM_TO_PRODUCE/2);   
	}

	return NULL;
}

void * consume(void *sum) 
{
	int *mysum = (int*)sum;
	*mysum = 0;
	for (int i = 0; i < NUM_TO_PRODUCE; i++) {
        element_t* ret = theQueue.dequeue();
        //std::cout << "consume: val is " << ret->val << std::endl;
    	*mysum += ret->val;
    	//std::cout << "consume: sum is " << *mysum << std::endl;
    	free(ret);
	}

	//std::cout << "consume: sum is " << *mysum << std::endl;
	pthread_exit(sum);
	//return(sum);
}

static int NUM_THREADS=5;

int factorial (int i) {
	if(i == 1) 
		return 1;
	else
		return (i + factorial(i-1));
}

int main() 
{
	pthread_t consumer_tid[NUM_THREADS], producer_tid[NUM_THREADS];

	
	int total_consumed_sum = 0;
	int *consumed = new int[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++) { 
		pthread_create(&(consumer_tid[i]), NULL, &consume, (void*)&consumed[i]);
		pthread_create(&(producer_tid[i]), NULL, &produce, NULL);
	}

	for (int i = 0; i < NUM_THREADS; i++) {
		void *retval;
		pthread_join(producer_tid[i], NULL);
		//pthread_join(consumer_tid[i], (void**)&consumed[i]);
		pthread_join(consumer_tid[i], (void**)&retval);
		int *retint = (int*)retval;
		//std::cout << "consumed sum is " << *retint << " " << consumed[i] << std::endl;
		total_consumed_sum += *retint;
	}
	assert(total_consumed_sum == NUM_THREADS * factorial(NUM_TO_PRODUCE - 1));
	delete [] consumed;
	return 0;
}
