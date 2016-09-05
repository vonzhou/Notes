Hive JDBC入门示例

## 安装Hadoop

## 安装Hive

## 使用Hive的JDBC接口

（1）建一个maven project，引入以下的依赖：

<dependency>
    <groupId>org.apache.hive</groupId>
    <artifactId>hive-exec</artifactId>
    <version>2.1.0</version>
</dependency>
<dependency>
    <groupId>org.apache.hive</groupId>
    <artifactId>hive-metastore</artifactId>
    <version>2.1.0</version>
</dependency>
<dependency>
    <groupId>org.apache.hive</groupId>
    <artifactId>hive-service</artifactId>
    <version>2.1.0</version>
</dependency>
<dependency>
    <groupId>org.apache.hive</groupId>
    <artifactId>hive-jdbc</artifactId>
    <version>2.1.0</version>
</dependency>

JDBC 客户端代码，这里只是为了走通这个过程，实现的功能很简单，查询u1_data表中记录的条数。

public class HiveJdbcClient {
    public static void main(String[] args) throws SQLException {
        try {
            Class.forName("org.apache.hive.jdbc.HiveDriver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        Connection con = DriverManager.getConnection("jdbc:hive2://localhost:10000/default", "", "");

        Statement stmt = con.createStatement();
        String tableName = "u1_data";
        ResultSet rs = stmt.executeQuery("select count(*) from " + tableName);
        if(rs.next()){
            System.out.println(rs.getString(1));
        }
    }
}


（2）配置Hadoop的 core-site.xml中的proxy user（使用你的用户名，比如我这里的“vonzhou”），否则会出现以下错误：

Caused by: java.lang.RuntimeException: org.apache.hadoop.ipc.RemoteException:User: vonzhou is not allowed to impersonate anonymous


Caused by: java.lang.RuntimeException: java.lang.RuntimeException: org.apache.hadoop.ipc.RemoteException(org.apache.hadoop.security.authorize.AuthorizationException): Unauthorized connection for super-user: vonzhou from IP 127.0.0.1

core-site.xml配置，具体需要改为自己的代理用户：

<property>
    <name>hadoop.proxyuser.vonzhou.groups</name>
    <value>*</value>
    <description>Allow the superuser vonzhou to impersonate any members of the group</description>
</property>
<property>
    <name>hadoop.proxyuser.vonzhou.hosts</name>
    <value>127.0.0.1,localhost</value>
    <description>The superuser can connect only the host to impersonate a user</description>
</property>

（3）启动Hadoop：

➜  sbin git:(master) ./start-all.sh

（4） 启动Hive Server2(这里使用的是 hiveserver2):

➜  apache-hive-2.1.0-bin git:(master) bin/hive --service hiveserver2
SLF4J: Class path contains multiple SLF4J bindings.
SLF4J: Found binding in [jar:file:/usr/local/dev/hive/apache-hive-2.1.0-bin/lib/log4j-slf4j-impl-2.4.1.jar!/org/slf4j/impl/StaticLoggerBinder.class]
SLF4J: Found binding in [jar:file:/usr/local/Cellar/hadoop/2.7.1/libexec/share/hadoop/common/lib/slf4j-log4j12-1.7.10.jar!/org/slf4j/impl/StaticLoggerBinder.class]
SLF4J: See http://www.slf4j.org/codes.html#multiple_bindings for an explanation.
➜  apache-hive-2.1.0-bin git:(master) lsof -i:10000
COMMAND  PID    USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
java    6614 vonzhou  442u  IPv4 0xd15bdc45c5568f1d      0t0  TCP *:ndmp (LISTEN)

（5）我在本机上，出现以下安全模式异常：

Caused by: org.apache.hive.service.cli.HiveSQLException: Failed to open new session: java.lang.RuntimeException: org.apache.hadoop.ipc.RemoteException(org.apache.hadoop.hdfs.server.namenode.SafeModeException): Cannot create directory /tmp/hive/anonymous. Name node is in safe mode.

解决的方法是关闭安全模式：

➜  sbin git:(master) hadoop dfsadmin -safemode leave
DEPRECATED: Use of this script to execute hdfs command is deprecated.
Instead use the hdfs command for it.

16/09/05 21:28:47 WARN util.NativeCodeLoader: Unable to load native-hadoop library for your platform... using builtin-java classes where applicable
Safe mode is OFF


（6）最终运行该程序，得到结果：

100000


## 参考

Proxy user - Superusers Acting On Behalf Of Other Users
http://hadoop.apache.org/docs/current/hadoop-project-dist/hadoop-common/Superusers.html
Setting Up HiveServer2
https://cwiki.apache.org/confluence/display/Hive/Setting+up+HiveServer2


