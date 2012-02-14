require "csv"

len = []
#timeo = []
copied = []
wait_count = []
receive_queue_enqueue_count = []
receive_queue_dequeue_count = []
async_wait_queue_enqueue_count = []
async_wait_queue_dequeue_count = []
prequeue_enqueue_count = []
prequeue_dequeue_count = []
dma_skb_copy_datagram_iovec_count = []
skb_copy_datagram_iovec_count = []
tcp_copy_to_iovec_count = []
dma_data_ready_count = []
receive_queue_data_ready_count = []

class Array
  def avg
    inject(0.0){|r,i| r+=i.to_i }/size
  end

  def variance
    a = avg
    inject(0.0){|r,i| r+=(i.to_i-a)**2 }/size
  end

  def standard_deviation
    Math.sqrt(variance)
  end

  def to_s
    "min:#{min} max:#{max} avg:#{avg} variance:#{variance} standard_deviation:#{standard_deviation}"
  end
end

CSV.open("/proc/tcp_recvmsg", "r", " ") do |row|
  len << row[1].to_i
#  timeo << row[2].to_i
  copied << row[3].to_i
  wait_count << row[4].to_i
  receive_queue_enqueue_count << row[5].to_i
  receive_queue_dequeue_count << row[6].to_i
  async_wait_queue_enqueue_count << row[7].to_i
  async_wait_queue_dequeue_count << row[8].to_i
  prequeue_enqueue_count << row[9].to_i
  prequeue_dequeue_count << row[10].to_i
  dma_skb_copy_datagram_iovec_count << row[11].to_i
  skb_copy_datagram_iovec_count << row[12].to_i
  tcp_copy_to_iovec_count << row[13].to_i
  dma_data_ready_count << row[14].to_i
  receive_queue_data_ready_count << row[15].to_i
end

puts "len:#{len}"
#puts "timeo:#{timeo}"
puts "copied:#{copied}"
puts "wait_count:#{wait_count}"
puts "receive_queue_enqueue_count:#{receive_queue_enqueue_count}"
puts "receive_queue_dequeue_count:#{receive_queue_dequeue_count}"
puts "async_wait_queue_enqueue_count:#{async_wait_queue_enqueue_count}"
puts "async_wait_queue_dequeue_count:#{async_wait_queue_dequeue_count}"
puts "prequeue_enqueue_count:#{prequeue_enqueue_count}"
puts "prequeue_dequeue_count:#{prequeue_dequeue_count}"
puts "dma_skb_copy_datagram_iovec_count:#{dma_skb_copy_datagram_iovec_count}"
puts "skb_copy_datagram_iovec_count:#{skb_copy_datagram_iovec_count}"
puts "tcp_copy_to_iovec_count:#{tcp_copy_to_iovec_count}"
puts "dma_data_ready_count:#{dma_data_ready_count}"
puts "receive_queue_data_ready_count:#{receive_queue_data_ready_count}"
