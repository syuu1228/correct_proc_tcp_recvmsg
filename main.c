#include <stdio.h>
#include <stdint.h>

struct tcp_recvmsg_procfs_entry {
	unsigned rxhash;
	unsigned len;
	long timeo;
	unsigned copied;
	unsigned wait_count;
	unsigned receive_queue_enqueue_count;
	unsigned receive_queue_dequeue_count;
	unsigned async_wait_queue_enqueue_count;
	unsigned async_wait_queue_dequeue_count;
	unsigned prequeue_enqueue_count;
	unsigned prequeue_dequeue_count;
	unsigned dma_skb_copy_datagram_iovec_count;
	unsigned skb_copy_datagram_iovec_count;
	unsigned tcp_copy_to_iovec_count;
	unsigned dma_data_ready_count;
	unsigned receive_queue_data_ready_count;
};

#define CORRECT_TR(tr, max, min, sum, member)		\
	do {						\
		if (tr.member > max.member)		\
			max.member = tr.member;		\
		if (tr.member < min.member)		\
			min.member = tr.member;		\
		sum.member += tr.member;		\
	} while (0)

#define AVG_TR(sum, avg, count, member)		\
	avg.member = sum.member / count

static inline void dump_tr(struct tcp_recvmsg_procfs_entry *tr)
{
	printf("len:%u\n", tr->len);
	printf("timeo:%ld\n", tr->timeo);
	printf("copied:%u\n", tr->copied);
	printf("wait_count:%d\n", tr->wait_count);
	printf("receive_queue_enqueue_count:%u\n", tr->receive_queue_enqueue_count);
	printf("receive_queue_dequeue_count:%u\n", tr->receive_queue_dequeue_count);
	printf("async_wait_queue_enqueue_count:%u\n", tr->async_wait_queue_enqueue_count);
	printf("async_wait_queue_dequeue_count:%u\n", tr->async_wait_queue_dequeue_count);
	printf("prequeue_enqueue_count:%u\n", tr->prequeue_enqueue_count);
	printf("prequeue_dequeue_count:%u\n", tr->prequeue_dequeue_count);
	printf("dma_skb_copy_datagram_iovec_count:%u\n", tr->dma_skb_copy_datagram_iovec_count);
	printf("skb_copy_datagram_iovec_count:%u\n", tr->skb_copy_datagram_iovec_count);
	printf("tcp_copy_to_iovec_count:%u\n", tr->tcp_copy_to_iovec_count);
	printf("dma_data_ready_count:%u\n", tr->dma_data_ready_count);
	printf("receive_queue_data_ready_count:%u\n", tr->receive_queue_data_ready_count);
}

static inline void print_header(void)
{
	printf("count rxhash len timeo copied wait_count ");
	printf("receive_queue_enqueue_count ");
	printf("receive_queue_dequeue_count ");
	printf("async_wait_queue_enqueue_count ");
	printf("async_wait_queue_dequeue_count ");
	printf("prequeue_enqueue_count ");
	printf("prequeue_dequeue_count ");
	printf("dma_skb_copy_datagram_iovec_count ");
	printf("skb_copy_datagram_iovec_count ");
	printf("tcp_copy_to_iovec_count ");
	printf("dma_data_ready_count ");
	printf("receive_queue_data_ready_count\n");
}

static inline void dump_line_tr(struct tcp_recvmsg_procfs_entry *tr, int count)
{
	printf("%d %x %u %ld %u %u %u %u %u %u %u %u %u %u %u %u %u\n",
	       count,
	       tr->rxhash,
	       tr->len,
	       tr->timeo,
	       tr->copied,
	       tr->wait_count,
	       tr->receive_queue_enqueue_count,
	       tr->receive_queue_dequeue_count,
	       tr->async_wait_queue_enqueue_count,
	       tr->async_wait_queue_dequeue_count,
	       tr->prequeue_enqueue_count,
	       tr->prequeue_dequeue_count,
	       tr->dma_skb_copy_datagram_iovec_count,
	       tr->skb_copy_datagram_iovec_count,
	       tr->tcp_copy_to_iovec_count,
	       tr->dma_data_ready_count,
	       tr->receive_queue_data_ready_count);
}


int main(int argc, char *argv[])
{
	struct tcp_recvmsg_procfs_entry tr, max, min, sum, avg;
	int count = 0;
	FILE *fp = fopen("/proc/tcp_recvmsg", "r");
	if (!fp)
		return -1;

	print_header();
	while (fscanf(fp, "%x %u %ld %u %u %u %u %u %u %u %u %u %u %u %u %u",
		      &tr.rxhash,
		      &tr.len,
		      &tr.timeo,
		      &tr.copied,
		      &tr.wait_count,
		      &tr.receive_queue_enqueue_count,
		      &tr.receive_queue_dequeue_count,
		      &tr.async_wait_queue_enqueue_count,
		      &tr.async_wait_queue_dequeue_count,
		      &tr.prequeue_enqueue_count,
		      &tr.prequeue_dequeue_count,
		      &tr.dma_skb_copy_datagram_iovec_count,
		      &tr.skb_copy_datagram_iovec_count,
		      &tr.tcp_copy_to_iovec_count,
		      &tr.dma_data_ready_count,
		      &tr.receive_queue_data_ready_count) == 16) {
		dump_line_tr(&tr, count);
		CORRECT_TR(tr, max, min, sum, len);
		CORRECT_TR(tr, max, min, sum, timeo);
		CORRECT_TR(tr, max, min, sum, copied);
		CORRECT_TR(tr, max, min, sum, wait_count);
		CORRECT_TR(tr, max, min, sum, receive_queue_enqueue_count);
		CORRECT_TR(tr, max, min, sum, receive_queue_dequeue_count);
		CORRECT_TR(tr, max, min, sum, async_wait_queue_enqueue_count);
		CORRECT_TR(tr, max, min, sum, async_wait_queue_dequeue_count);
		CORRECT_TR(tr, max, min, sum, prequeue_enqueue_count);
		CORRECT_TR(tr, max, min, sum, prequeue_dequeue_count);
		CORRECT_TR(tr, max, min, sum, dma_skb_copy_datagram_iovec_count);
		CORRECT_TR(tr, max, min, sum, skb_copy_datagram_iovec_count);
		CORRECT_TR(tr, max, min, sum, tcp_copy_to_iovec_count);
		CORRECT_TR(tr, max, min, sum, dma_data_ready_count);
		CORRECT_TR(tr, max, min, sum, receive_queue_data_ready_count);
		count++;
	}
	AVG_TR(sum, avg, count, len);
	AVG_TR(sum, avg, count, timeo);
	AVG_TR(sum, avg, count, copied);
	AVG_TR(sum, avg, count, wait_count);
	AVG_TR(sum, avg, count, receive_queue_enqueue_count);
	AVG_TR(sum, avg, count, receive_queue_dequeue_count);
	AVG_TR(sum, avg, count, async_wait_queue_enqueue_count);
	AVG_TR(sum, avg, count, async_wait_queue_dequeue_count);
	AVG_TR(sum, avg, count, prequeue_enqueue_count);
	AVG_TR(sum, avg, count, prequeue_dequeue_count);
	AVG_TR(sum, avg, count, dma_skb_copy_datagram_iovec_count);
	AVG_TR(sum, avg, count, skb_copy_datagram_iovec_count);
	AVG_TR(sum, avg, count, tcp_copy_to_iovec_count);
	AVG_TR(sum, avg, count, dma_data_ready_count);
	AVG_TR(sum, avg, count, receive_queue_data_ready_count);
	
	printf("\n[max]\n");
	dump_tr(&max);
	printf("\n[min]\n");
	dump_tr(&min);
	printf("\n[avg]\n");
	dump_tr(&avg);
} 
