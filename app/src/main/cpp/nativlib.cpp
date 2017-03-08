#include <jni.h>
#include <string>
#include <stdlib.h>
//每个native函数，都至少两个参数，(JNIEnv, jclass或者jobject)
//1，当native方法为静态方法时：
// jclass代表native方法所属类的class对象（MainActivity.class）
//2,当native方法为非静态方法时
//jobject为native方法所属的对象

//JNI的基本数据类型
//java的基本数据类型和JNI的数据类型的映射关系
//java类型->JNI 类型->C类型
//引用数据类型（对象）
//String jstring
//object jobject
//数组，基本数据类型的数组
//byte[] jByteArray
//对象数组
//object[] (String[])  jobjectArray

extern "C"
JNIEXPORT jstring JNICALL
Java_com_longshihan_testndk_MainActivity_getint2FromC(JNIEnv *env, jobject instance, jint i) {
    // TODO

    std::string hello = "" + i;
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_longshihan_testndk_MainActivity_getstring2FromC(JNIEnv *env, jobject instance) {

    // TODO

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_longshihan_testndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//c/c++访问java
//1.访问属性
//修改属性key
extern "C"
JNIEXPORT jstring JNICALL
Java_com_longshihan_testndk_MainActivity_accessFiled(JNIEnv *env, jobject instance) {
    //得到jclass,相当于反射得到MainActivity.class
    jclass cls = env->GetObjectClass(instance);
    //jfieldID
    //属性名称，属性签名
    jfieldID fid = env->GetFieldID(cls, "key", "Ljava/lang/String;");
    //拿到属性,jason->super jason
    //获取了key属性的值
    jstring jstring1 = (jstring) env->GetObjectField(instance, fid);

    //jsting->c字符串
    char *c_str = (char *) env->GetStringUTFChars(jstring1, 0);
    //拼接
    char text[20] = "super ";
    strcat(text, c_str);
    //c字符串转成jstring
    jstring new_jstr = env->NewStringUTF(text);
    //修改key
    env->SetObjectField(instance, fid, new_jstr);
    return new_jstr;
}
//2.访问静态属性
extern "C"
JNIEXPORT void JNICALL
Java_com_longshihan_testndk_MainActivity_accessCountFiled(JNIEnv *env, jobject instance) {
    //jclass
    jclass cls = env->GetObjectClass(instance);
    //jfield
    jfieldID fid = env->GetStaticFieldID(cls, "COUNT", "I");
    //GetStatic<TYpe>Field
    jint count = env->GetStaticIntField(cls, fid);
    count++;
    //修改
    //SetStatic<type>Field
    env->SetStaticIntField(cls, fid, count);
}
//访问java方法
extern "C"
JNIEXPORT void JNICALL
Java_com_longshihan_testndk_MainActivity_accessMethod(JNIEnv *env, jobject instance) {
    //jclass
    jclass cls = env->GetObjectClass(instance);
    //jmethodID
    jmethodID fid = env->GetMethodID(cls, "getRandomInt", "(I)I");
    //调用
    jint random = env->CallIntMethod(instance, fid, 200);
    printf("random num :%ld", random);
}

//访问java静态方法
extern "C"
JNIEXPORT void JNICALL
Java_com_longshihan_testndk_MainActivity_accessStaticMethod(JNIEnv *env, jobject instance) {
    //jclass
    jclass cls = env->GetObjectClass(instance);
    //jmethodID
    //Get Static Method ID
    jmethodID fid = env->GetStaticMethodID(cls, "getUUID", "()Ljava/lang/String;");
    //调用
    //Call Static Object Method
    jstring uuid = (jstring) env->CallStaticObjectMethod(cls, fid);
    //随机文件名称uuid_str.txt
    //jsring->char *
    //isCopy ,JNI_FALSE=java和C操作的是一个字符串
    char *uuid_str = (char *) env->GetStringUTFChars(uuid, JNI_FALSE);
    //拼接
    char filename[100];
    sprintf(filename, "D://file//%s.txt", uuid_str);
    FILE *fp = fopen(filename, "w");
    fputs("i love C", fp);
    fclose(fp);
}

//访问java父类方法
extern "C"
JNIEXPORT void JNICALL
Java_com_longshihan_testndk_MainActivity_accessNonvirtualMethod(JNIEnv *env, jobject instance) {
    //jclass
    jclass cls = env->GetObjectClass(instance);
    //jmethodID
    //获取man属性（对象）
    jfieldID fid = env->GetFieldID(cls, "human", "Lcom/longshihan/testndk/Human;");
    jobject human_obj = env->GetObjectField(instance, fid);
    //执行sayhi方法
    jclass human_cls = env->FindClass("com/longshihan/testndk/Human");
    jmethodID mid = env->GetMethodID(human_cls, "sayHi", "()V");
    //调用
    //env->CallObjectMethod(human_obj,mid);
    //调用父类的方法
    env->CallNonvirtualVoidMethod(human_obj, human_cls, mid);
}

//传入中文
extern "C"
JNIEXPORT jstring JNICALL
Java_com_longshihan_testndk_MainActivity_chinessChar(JNIEnv *env, jobject instance, jstring in_) {
    //输出
    const char *in = env->GetStringUTFChars(in_, 0);
    env->ReleaseStringUTFChars(in_, in);
    //c字符串-》java
    const char *c_str = "啦啦啦啦啦";
    //char c_str[] = "马蓉与宋喆";
    //jstring jstr = (*env)->NewStringUTF(env, c_str);
    //执行String(byte bytes[], String charsetName)构造方法需要的条件
    //1.jmethodID
    //2.byte数组
    //3.字符编码jstring
    jclass str_clss = env->FindClass("java/lang/String");
    jmethodID constructor_mid = env->GetMethodID(str_clss, "<init>",
                                                 "([BLjava/lang/String;)V");//构造方法
    //jbyte -> char
    //jbyteArray -> char[]
    jbyteArray bytes = env->NewByteArray(strlen(c_str));
    //byte数组赋值
    //0->strlen(c_str)，从头到尾
    //对等于，从c_str这个字符数组，复制到bytes这个字符数组
    env->SetByteArrayRegion(bytes, 0, strlen(c_str), (const jbyte *) c_str);

    //字符编码jstring
    jstring charsetName = env->NewStringUTF("UTF-8");
//调用构造函数，返回编码之后的jstring
    jstring jstring1 = (jstring) env->NewObject(str_clss, constructor_mid, bytes, charsetName);
    // jstring  jstring1=env->NewStringUTF(c_str);
    return jstring1;
}


int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}


//传入数组
extern "C"
JNIEXPORT void JNICALL
Java_com_longshihan_testndk_MainActivity_giveArray(JNIEnv *env, jobject instance, jintArray arr_) {
    //得到jint指针->c int 数组
    jint *arr = env->GetIntArrayElements(arr_, NULL);
    long len = env->GetArrayLength(arr_);

    qsort(arr, len, sizeof(jint), compare);

    //同步
    env->ReleaseIntArrayElements(arr_, arr, 0);
}

//JNI 引用变量
//引用类型：局部引用和全局引用
//作用：在JNI中告知虚拟机何时回收一个JNI变量

//局部引用，通过DeleteLocalRef手动释放
//1，访问一个很大的对象，使用完之后，还要进行复杂的耗时操作，
//2，创建大量的局部引用，占用了很多空间，而且局部引用和后面的操作没有关联性
//模拟创建循环数组
void testArr(JNIEnv *env, jobject instance) {
    int i = 0;
    for (; i < 5; ++i) {
        //创建date对象
        jclass cls = env->FindClass("java/util/Date");
        jmethodID jmethodID1 = env->GetMethodID(cls, "<init>", "()V");
        jobject jobject1 = env->NewObject(cls, jmethodID1);
        //。。。。。此处省略XXX行
        //不在使用jobject对象
        //通知垃圾回收器这些对象
        env->DeleteLocalRef(jobject1);

        //。。。。。此处省略XXX行

    }
}

//全局
//共享，跨多个线程，手动控制内存使用
jstring global_str;

//创建
void testQuanju(JNIEnv *env, jobject instance) {
    jstring obj = env->NewStringUTF("jni development");
    global_str = (jstring) env->NewGlobalRef(obj);
}

//获取
jstring testHuode(JNIEnv *env, jobject instance) {
    return global_str;
}

//释放
void testShifang(JNIEnv *env, jobject instance) {
    env->DeleteGlobalRef(global_str);
    jthrowable exception = env->ExceptionOccurred();
    if (exception != NULL) {
        //让java可以执行，情况异常信息
        env->ExceptionClear();
        //补救措施

    }
}
//缓存
extern "C"
JNIEXPORT void JNICALL
Java_com_longshihan_testndk_MainActivity_cache(JNIEnv *env, jobject instance) {

    //jclass
    jclass cls = env->GetObjectClass(instance);
    //jmethodID
    //获取man属性（对象）
    static jfieldID fid = NULL;
    if (fid==NULL){
        fid=env->GetFieldID(cls,"key","Ljava/lang/String;");
    }


}