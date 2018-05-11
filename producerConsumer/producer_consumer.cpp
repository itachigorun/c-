#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <deque>

struct Item {
	std::deque<int> item_buffer;
	std::mutex mtx;
	std::condition_variable repo_not_full; // 条件变量, 指示产品缓冲区不为满.
	std::condition_variable repo_not_empty; // 条件变量, 指示产品缓冲区不为空.
} gItem; // 产品库全局变量, 生产者和消费者操作该变量.


void ProduceItem(Item &item, int num)
{
	std::unique_lock<std::mutex> lock(item.mtx);
	// item buffer is full
	while (item.item_buffer.size() == 50){
		std::cout << "Producer buff is full..."<< std::endl;
		item.repo_not_full.wait(lock); // 生产者等待"产品库缓冲区不为满"这一条件发生.
	}

	item.item_buffer.emplace_back(num);
	item.repo_not_empty.notify_all(); // 通知消费者产品库不为空.
	lock.unlock(); 
}

int ConsumeItem(Item &item)
{
	int data;
	std::unique_lock<std::mutex> lock(item.mtx);
	// item buffer is empty, just wait here.
	while (item.item_buffer.empty()) {
		std::cout << "Consumer is waiting for items..."<< std::endl;
		item.repo_not_empty.wait(lock); // 消费者等待"产品库缓冲区不为空"这一条件发生.
	}

	data = item.item_buffer.front();
	item.item_buffer.pop_front();

	item.repo_not_full.notify_all(); // 通知消费者产品库不为满.
	lock.unlock(); 

	return data; 
}

void ProducerTask(int ItemToProduce) // 生产者任务
{
	for (int i = 1; i <= ItemToProduce; ++i) {
		std::cout << "Produce the " << i << "^th item..." << std::endl;
		ProduceItem(gItem, i); 
	}
}

void ConsumerTask(int ItemToProduce) // 消费者任务
{
	static int count = 0;
	while (1) {
		int item = ConsumeItem(gItem); 
		std::cout << "Consume the " << item << "^th item" << std::endl;
		if (++count == ItemToProduce) break;
	}
}

int main()
{
	std::thread producer(ProducerTask, 100); // 创建生产者线程.
	std::thread consumer(ConsumerTask, 100); // 创建消费者线程.
	producer.join();
	consumer.join();
	return 0;
}