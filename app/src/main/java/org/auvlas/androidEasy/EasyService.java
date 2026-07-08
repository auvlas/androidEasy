package org.auvlas.androidEasy;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class EasyService extends Service {

    @Override
    public void onCreate() {
        super.onCreate();

        Log.d("AndroidEasy", "The library core has been successfully launched in the system!");

        System.loadLibrary("sapper");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d("AndroidEasy", "The client application has connected to the service.");

        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        Log.d("AndroidEasy", "The library process is terminating.");
    }
}
