



```
  		<dependency>
            <groupId>org.apache.kafka</groupId>
            <artifactId>kafka_2.11</artifactId>
            <version>0.8.2.1</version>
        </dependency>
```	

```java
public class MessageProducer {

    private Producer<String,String> producer;

    public static void main(String[] args) {
        new MessageProducer().start();
    }

    public void init(){
        Properties props = new Properties();
        props.put("metadata.broker.list", "localhost:9092");   // broker 集群列表
        props.put("serializer.class", "kafka.serializer.StringEncoder");
        props.put("request.required.acks", "1");
        ProducerConfig config = new ProducerConfig(props);
        // 泛型参数分别表示 The first is the type of the Partition key, the second the type of the message
        producer = new Producer<String, String>(config);
    }

    public void produceMsg(){
        // 构建发送的消息
        long timestamp = System.currentTimeMillis();
        String msg = "Msg" + timestamp;
        String topic = "test";  // 确保有这个topic
        System.out.println("发送消息" + msg);
        String key = "Msg-Key" + timestamp;

        KeyedMessage<String, String> data = new KeyedMessage<String, String>(topic, key, msg);

        producer.send(data);
    }

    public void start() {
        System.out.println("Turning on Kafka consumer ...");
        Executors.newSingleThreadExecutor().execute(new Runnable() {
            public void run() {
                init();
                while (true) {
                    try {
                        produceMsg();
                        Thread.sleep(2000);
                    } catch (Throwable e) {
                        if (producer != null) {
                            try {
                                producer.close();
                            } catch (Throwable e1) {
                                System.out.println("Turn off Kafka consumer error! " + e);
                            }
                        }
                    }

                }

            }
        });
    }
}
```





```java
public class MessageConsumer {
    private ConsumerConnector consumer;
    private String topic;

    public static void main(String[] arg) {
        new MessageConsumer().start();
    }

    public void init(){
        // 指定 zookeeper 的地址
        String zookeeper = "localhost:2181";
        String topic = "test";
        String groupId = "test-group";

        Properties props = new Properties();
        props.put("zookeeper.connect", zookeeper);
        props.put("group.id", groupId);
        props.put("zookeeper.session.timeout.ms", "6000");
        props.put("zookeeper.sync.time.ms", "200");
        props.put("auto.commit.interval.ms", "1000");


        consumer = Consumer.createJavaConsumerConnector(new ConsumerConfig(props));
        this.topic = topic;
    }
    public void consume() {
        Map<String, Integer> topicCountMap = new HashMap<String, Integer>();
        topicCountMap.put(topic, 1);
        /**
         * createMessageStreams 为每个topic创建 message stream
         */
        Map<String, List<KafkaStream<byte[], byte[]>>> messageStreams = consumer.createMessageStreams(topicCountMap);
        KafkaStream<byte[], byte[]> stream = messageStreams.get(topic).get(0);
        ConsumerIterator<byte[], byte[]> iterator = stream.iterator();
        while (iterator.hasNext()) {
            try {
                String message = new String(iterator.next().message());
                System.out.println("收到消息" + message);
            } catch (Throwable e) {
                System.out.println(e.getCause());
            }
        }

    }

    public void start() {
        System.out.println("Turning on Kafka consumer ...");
        Executors.newSingleThreadExecutor().execute(new Runnable() {

            public void run() {
                init();
                while (true) {
                    try {
                        consume();
                    } catch (Throwable e) {
                        if (consumer != null) {
                            try {
                                consumer.shutdown();
                            } catch (Throwable e1) {
                                System.out.println("Turn off Kafka consumer error! " + e);
                            }
                        }
                    }
                }
            }
        });
    }
}
```









注意kafka的artifact_Id（比如我用的kafka_2.11）后面的版本号一定要和本机装的Scala版本一致，否则会报以下错误。

```java
Exception in thread "main" java.lang.NoClassDefFoundError: scala/collection/GenTraversableOnce$class
	at kafka.utils.Pool.<init>(Pool.scala:28)
	at kafka.consumer.ZookeeperConsumerConnector.<init>(ZookeeperConsumerConnector.scala:91)
	at kafka.javaapi.consumer.ZookeeperConsumerConnector.<init>(ZookeeperConsumerConnector.scala:66)
	at kafka.javaapi.consumer.ZookeeperConsumerConnector.<init>(ZookeeperConsumerConnector.scala:69)
	at kafka.consumer.Consumer$.createJavaConsumerConnector(ConsumerConnector.scala:105)
	at kafka.consumer.Consumer.createJavaConsumerConnector(ConsumerConnector.scala)
	at com.vonzhou.learn.message.KafkaConsumer.<init>(KafkaConsumer.java:23)
	at com.vonzhou.learn.message.KafkaConsumer.main(KafkaConsumer.java:72)
	at sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.lang.reflect.Method.invoke(Method.java:497)
	at com.intellij.rt.execution.application.AppMain.main(AppMain.java:144)
Caused by: java.lang.ClassNotFoundException: scala.collection.GenTraversableOnce$class
	at java.net.URLClassLoader.findClass(URLClassLoader.java:381)
	at java.lang.ClassLoader.loadClass(ClassLoader.java:424)
	at sun.misc.Launcher$AppClassLoader.loadClass(Launcher.java:331)
	at java.lang.ClassLoader.loadClass(ClassLoader.java:357)
	... 13 more
```