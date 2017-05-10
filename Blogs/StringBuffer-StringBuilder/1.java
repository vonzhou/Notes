StringBuffer 和 StringBuilder 的区别是什么？

## String 的问题

因为String是immutable的，每次的操作都会创建一个新的String对象，当操作频繁的时候就会带来开销，而StringBuilder，StringBuffer内部维护的是字符数组，每次的操作都是改变字符数组的状态，避免创建大量的String对象。



## 区别是什么？

答：StringBuffer是同步的（synchronized），而 StringBuilder，所以StringBuilder效率更高，锁的获取和释放会带来开销。


## 看看代码

不论是创建StringBuffer 还是 StringBuilder对象，都是创建一个容量为16的字符数组。

/**
* The value is used for character storage.
*/
char[] value;

/**
* The count is the number of characters used.
*/
int count;

AbstractStringBuilder(int capacity) {
    value = new char[capacity];
}

区别就是append方法，前者有synchronized关键字修饰。

StringBuffer的append方法：

public synchronized StringBuffer append(String str) {
    toStringCache = null;
    super.append(str);
    return this;
}

StringBuilder的append方法：

public StringBuilder append(String str) {
    super.append(str);
    return this;
}

虽然实际的实现是一样的。

public AbstractStringBuilder append(String str) {
    if (str == null)
        return appendNull(); // 如果是null的话，就添加字符串"null"
    int len = str.length();
    ensureCapacityInternal(count + len);
    str.getChars(0, len, value, count); // 字符数组的拷贝
    count += len;
    return this;
}

##　toString()方法

虽然StringBuffer使用了缓存，但是本质上都一样，每次toString()都会创建一个新的String对象，而不是使用底层的字符数组，我的理解是：StringBuffer/StringBuilder的存在是为了高效的操作字符串（字符数组）的状态，
但是当我们使用toString()的时候一定是一个稳定的状态，具有确切的行为，底层的字符数组仍然是可有变化的。

public synchronized String toString() {
    if (toStringCache == null) {
        toStringCache = Arrays.copyOfRange(value, 0, count);
    }
    return new String(toStringCache, true);
}

public String toString() {
    // Create a copy, don't share the array
    return new String(value, 0, count);
}