#include <deque>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

struct Item {
	std::deque<int> item_buffer;
	size_t produced_item_counter;
	size_t consumed_item_counter;
	std::mutex mtx;
	std::mutex produced_item_counter_mtx;
	std::mutex consumed_item_counter_mtx;
	std::condition_variable repo_not_full;
	std::condition_variable repo_not_empty;
} gItem;

void ProduceItem(Item &item, int num)
{
	std::unique_lock<std::mutex> lock(item.mtx);
	while (item.item_buffer.size()==100) { // item buffer is full, just wait here.
		std::cout << "Produce item is full..."<< std::endl;
		(item.repo_not_full).wait(lock);
	}

	item.item_buffer.emplace_back(num);

	item.repo_not_empty.notify_all();
	lock.unlock();
}

int ConsumeItem(Item &item)
{
	int data;
	std::unique_lock<std::mutex> lock(item.mtx);
	// item buffer is empty, just wait here.
	while (item.item_buffer.empty()) {
		std::cout << "Consumer is waiting for items...\n";
		(item.repo_not_empty).wait(lock);
	}

	data = item.item_buffer.front();
	item.item_buffer.pop_front();

	item.repo_not_full.notify_all();
	lock.unlock();

	return data;
}

void ProducerTask(int numToProduce)
{
	bool ready_to_exit = false;
	while (1) {
		std::unique_lock<std::mutex> lock(gItem.produced_item_counter_mtx);
		if (gItem.produced_item_counter < numToProduce) {
			++(gItem.produced_item_counter);
			ProduceItem(gItem, gItem.produced_item_counter);
			std::cout << "Producer thread " << std::this_thread::get_id()
				<< " is producing the " << gItem.produced_item_counter
				<< "^th item" << std::endl;
		}
		else
			ready_to_exit = true;
		lock.unlock();
		if (ready_to_exit == true) break;
	}
	std::cout << "Producer thread "<< std::this_thread::get_id() 
		      << " is exiting..." << std::endl;
}

void ConsumerTask(int numToConsum)
{
	bool ready_to_exit = false;
	while (1) {
		std::unique_lock<std::mutex> lock(gItem.consumed_item_counter_mtx);
		if (gItem.consumed_item_counter < numToConsum) {
			int item = ConsumeItem(gItem);
			++(gItem.consumed_item_counter);
			std::cout << "Consumer thread " << std::this_thread::get_id()
				<< " is consuming the " << item << "^th item" << std::endl;
		}
		else 
			ready_to_exit = true;
		lock.unlock();
		if (ready_to_exit == true) break;
	}
	std::cout << "Consumer thread " << std::this_thread::get_id() 
		      << " is exiting..." << std::endl;
}


int main()
{
	std::thread producer1(ProducerTask, 100);
	std::thread producer2(ProducerTask, 100);
	std::thread producer3(ProducerTask, 100);
	std::thread producer4(ProducerTask, 100);

	std::thread consumer1(ConsumerTask, 100);
	std::thread consumer2(ConsumerTask, 100);
	std::thread consumer3(ConsumerTask, 100);
	std::thread consumer4(ConsumerTask, 100);

	producer1.join();
	producer2.join();
	producer3.join();
	producer4.join();

	consumer1.join();
	consumer2.join();
	consumer3.join();
	consumer4.join();

	return 0;
}