package com.longshihan.testndk;

import android.util.Log;

/**
 * @author Administrator
 * @time 2017/3/6 14:55
 * @des ${TODO}
 * @updateAuthor $Author$
 * @updateDate $Date$
 * @updateDes ${TODO}
 */

public class Man extends Human {

    @Override
    public void sayHi() {
        Log.d("info","相互打招呼");

    }
    public void sayHi2() {
        super.sayHi();
    }

}
