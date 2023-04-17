#include <thread>
#include <iostream>
using namespace std;
 
#include <unistd.h>
 
#include <event2/event.h>

#include "testUtil.h"
#include "XThread.h"
#include "XTask.h"

static void Notify_cb(evutil_socket_t fd, short which, void *arg) {
	XThread *t = (XThread*)arg;
	t->Notify(fd, which);
}

void XThread::Notify(evutil_socket_t fd, short which) {
	testout(id << " thread At Notify()");
	char buf[2] = { 0 };
 
	int re = read(fd, buf, 1);
	if (re < 0)
		return;
	cout << id << " thread recv" << buf << endl;
}


void XThread::Start() {
	testout(id << " thread At Start()");
	Setup();
	thread th(&XThread::Main, this);
	th.detach();
}


void XThread::Main() {
	cout << id << " thread::Main() begin" << endl;
	event_base_dispatch(base);
	event_base_free(base);
	cout << id << " thread::Main() end" << endl;
}


bool XThread::Setup() {
	testout(id << " thread At Setup");

	int fds[2];

	if (pipe(fds)) {
		cerr << "pipe failed" << endl;
		return false;
	}

	notify_send_fd = fds[1];

	event_config *ev_conf = event_config_new();
	event_config_set_flag(ev_conf, EVENT_BASE_FLAG_NOLOCK);
	this->base = event_base_new_with_config(ev_conf);
	event_config_free(ev_conf);
	if (!base) {
		cout << "event_base_new_with_config error!" << endl;
		return false;
	}
	event *ev = event_new(base, fds[0], EV_READ | EV_PERSIST, Notify_cb, this);
	event_add(ev, 0);

	return true;
}

void XThread::Activate() {
	testout(id << " thread At Activate()");


	int re = write(notify_send_fd, "c", 1);

	if (re <= 0) {
		cerr << "XThread::Activate() fail" << endl;
	}
	XTask *t = NULL;
	tasks_mutex.lock();
	if (tasks.empty()) {
		tasks_mutex.unlock();
		return;
	}
	t = tasks.front();
	tasks.pop_front();
	tasks_mutex.unlock();
	t->Init();
}


void XThread::AddTack(XTask *t) {
	if (!t) return;

	t->base = this->base;

	tasks_mutex.lock();
	tasks.push_back(t);
	tasks_mutex.unlock();
}

XThread::XThread() {

}
XThread::~XThread() {

}
