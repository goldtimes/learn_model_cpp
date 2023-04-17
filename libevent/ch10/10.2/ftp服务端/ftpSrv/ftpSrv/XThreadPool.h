#pragma once
#include <vector>

class XThread;
class XTask;
class XThreadPool
{
public:

	static XThreadPool *Get() {
		static XThreadPool p;
		return &p;
	}

	void Init(int threadCount);


	void Dispatch(XTask*);
private:
	int threadCount;
	int lastThread = -1;
	std::vector<XThread *> threads;
	XThreadPool() {};
};


