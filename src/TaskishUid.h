/* -*- Mode: C++; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#ifndef RR_TASKISH_UID_H_
#define RR_TASKISH_UID_H_

#include <inttypes.h>
#include <unistd.h>

class AddressSpace;
class Task;
class TaskGroup;

/**
 * An ID that's unique within a Session (but consistent across
 * multiple ReplaySessions for the same trace), used by Tasks, TaskGroups
 * and AddressSpaces.
 * This is needed because tids can be recycled during a long-running session.
 */
template <class T> class TaskishUid {
public:
  TaskishUid() : tid_(0), serial_(0) {}
  TaskishUid(pid_t tid, uint32_t serial) : tid_(tid), serial_(serial) {}
  TaskishUid(const TaskishUid<T>& other) = default;
  bool operator==(const TaskishUid<T>& other) const {
    return tid_ == other.tid_ && serial_ == other.serial_;
  }
  bool operator<(const TaskishUid<T>& other) const {
    if (tid_ < other.tid_) {
      return true;
    }
    if (tid_ > other.tid_) {
      return false;
    }
    return serial_ < other.serial_;
  }
  pid_t tid() const { return tid_; }
  uint32_t serial() const { return serial_; }

private:
  pid_t tid_;
  uint32_t serial_;
};

typedef TaskishUid<AddressSpace> AddressSpaceUid;
typedef TaskishUid<Task> TaskUid;
typedef TaskishUid<TaskGroup> TaskGroupUid;

#endif // RR_TASKISH_UID_H_
