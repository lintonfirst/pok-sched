
class Process:
    def __init__(self, name, arrive_time, serve_time):
        self.name = name  # 进程名
        self.arrive_time = arrive_time  # 到达时间
        self.serve_time = serve_time  # 需要服务的时间
        self.left_serve_time = serve_time  # 剩余需要服务的时间
        self.finish_time = 0  # 完成时间
        self.cycling_time = 0  # 周转时间
        self.w_cycling_time = 0  # 带权周转时间


class Queue:
    def __init__(self, level, process_list):
        self.level = level  # 层级
        self.process_list = process_list  # 进程列表
        self.q = 0  # 时间片

    def size(self):
        return len(self.process_list)

    def get(self, index):
        return self.process_list[index]

    def add(self, process):
        self.process_list.append(process)

    def delete(self, index):
        self.process_list.remove(self.process_list[index])


class RR:
    def __init__(self, process_list, q):
        self.process_list = process_list
        self.q = q

    def scheduling(self):
        process_list.sort(key=lambda x: x.arrive_time)  # 按照.arrive_time进行排序
        len_queue = len(self.process_list)  # 进程队列的长度
        index = int(0)  # 索引
        q = self.q  # 时间片
        running_time = int(0)  # 已经运行了的时间

        while (True):
            current_process = self.process_list[index % len_queue]
            if current_process.left_serve_time > 0:
                if current_process.left_serve_time >= q:
                    running_time += q
                    current_process.left_serve_time -= q

                else:
                    running_time += current_process.left_serve_time
                    current_process.left_serve_time = 0

            if current_process.left_serve_time == 0:
                current_process.finish_time = running_time
                current_process.cycling_time = current_process.finish_time - current_process.arrive_time
                current_process.w_cycling_time = float(current_process.cycling_time) / current_process.serve_time
                self.process_list.remove(current_process)
                len_queue = len(self.process_list)
                index -= 1
            index += 1
            if len(self.process_list) == 0:
                break
            if index >= len(self.process_list):
                index = index % len_queue


class MulitlevedFeedbackQueue():
    def __init__(self, queue_list, q_first):
        self.queue_list = queue_list
        self.q_first = q_first

    def scheduling(self):
        q_list = self.queue_list  # 当前队列集合
        q_first = self.q_first  # 第一个队列的时间片

        for i in range(len(q_list)):
            # 确定每个队列的时间片
            if i == 0:
                q_list[i].q = q_first
            else:
                q_list[i].q = q_list[i - 1].q * 2

            # 从第一个队列开始执行时间片
            # 先判断是否是最后一个队列，最后一个队列直接执行RR调度算法
            # 不是最后一个队列的话，就执行当前队列时间片后判断是否有必要加入到下一个队列的末尾
            if i == len(q_list) - 1:
                print('**************对最后一个队列执行RR调度算法*************')
                # print(q_list[i].process_list[])
                # 最后一个队列重新设置到达时间
                for t in range(len(q_list[i].process_list)):
                    q_list[i].process_list[t].arrive_time = t
                rr_last_queue = RR(q_list[i].process_list, q_list[i].q)
                rr_last_queue.scheduling()
            else:
                currentQueue = q_list[i]

                index = int(0)
                while True:
                    if currentQueue.get(index).left_serve_time > q_list[i].q:
                        currentQueue.get(index).left_serve_time -= q_list[i].q
                        print('第  %d  队列时间片: %d' % (i, q_list[i].q))
                        print('进程没有执行完毕,需要添加至下一队列末尾：进程名称：%s ' % (currentQueue.get(index).name))
                        # 将当前进程扔到下一个队列的尾部
                        q_list[i + 1].add(currentQueue.get(index))
                        index += 1
                    else:
                        print('服务完成并弹出:', currentQueue.get(index).name)
                        currentQueue.get(index).left_serve_time = 0
                        currentQueue.delete(index)

                    if index == currentQueue.size():
                        break

if __name__ == '__main__':
    process_list = []
    print('#################################################################')
    print('-----------------------测试多级反馈队列调度算法----------------------')
    print('#################################################################')
    processA = Process('A', 0, 4)
    processB = Process('B', 1, 3)
    processC = Process('C', 2, 4)
    processD = Process('D', 3, 2)
    processE = Process('E', 4, 4)

    process_list0, process_list1, process_list2 = [], [], []
    process_list0.append(processA), process_list0.append(processB)
    process_list1.append(processC), process_list1.append(processD)
    process_list2.append(processE)

    # 队列
    queue_list = []
    queue0 = Queue(0, process_list0)
    queue1 = Queue(1, process_list1)
    queue2 = Queue(2, process_list2)
    queue_list.append(queue0), queue_list.append(queue1), queue_list.append(queue2)
    # 使用多级反馈队列调度算法,第一队列时间片为1
    mfq = MulitlevedFeedbackQueue(queue_list, 1)
    mfq.scheduling()
