package com.longshihan.testndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import java.util.Random;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-libs");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        // Log.d("info", "修改前"+COUNT);
        // accessCountFiled();
        // Log.d("info", "修改后"+COUNT);
        // accessMethod();
        //accessStaticMethod();
        // tv.setText(accessFiled() + COUNT);

        //accessNonvirtualMethod();
        //String out = chinessChar("龙贺");
        //Log.d("info", out);
        // tv.setText(out);
        int[] arr = new int[]{4, 6, 3, 2, 7};
      //  giveArray(arr);
        for (int a : arr) {
            Log.d("info", "数据data：" + a);
        }
        cache();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getstring2FromC();

    public native String getint2FromC(int i);

    public String key = "jason";

    //访问属性，返回修改之后的属性
    public native String accessFiled();

    public static int COUNT = 9;

    public native void accessCountFiled();

    //产生指定范围的随机数
    public int getRandomInt(int max) {
        Log.d("info", "执行了。。。。。。。。。。。。");
        return new Random().nextInt(max);
    }

    public native void accessMethod();

    //产生UUID，
    public static String getUUID() {
        return UUID.randomUUID().toString();
    }

    public native void accessStaticMethod();

    public native void accessNonvirtualMethod();

    public Human human = new Man();

    public native String chinessChar(String in);

    public native void giveArray(int[] arr);


    public native void cache();

}
