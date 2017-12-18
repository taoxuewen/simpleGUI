package com.stimulaltor.taoxuewen.stimualtor;

import android.net.Uri;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.*;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.common.api.GoogleApiClient;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.lang.*;
import java.net.Socket;
import java.io.IOException;
//import java.io.InputStream;
//import java.io.OutputStream;
import java.net.InetAddress;
//import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {

    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;
    boolean isConnect=true;//连接还是断开
    boolean isStim=true;//刺激还是停止
    Button ConnectButton;//定义连接按钮
    Button stimButton;//定义刺激按钮
    private EditText mANum;//定义电流值
    RadioButton channel1;//单选按钮1
    RadioButton channel2;//单选按钮2
    boolean isCheck;//是否被选中
    EditText status;//状态栏
    Socket sock;//创建套接字
    int channelSelction=1;//当前通道


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mANum=(EditText)findViewById(R.id.Edit_mA);
        channel1=(RadioButton)findViewById(R.id.channel1);
        channel2=(RadioButton)findViewById(R.id.channel2);
        stimButton=(Button)findViewById(R.id.bt_start_stim);
        stimButton.setEnabled(false);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        status=(EditText)findViewById(R.id.text_status);
        ConnectButton = (Button)findViewById(R.id.bt_connect);
        ConnectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                status.setText("状态:未连接");
                if (isConnect) {
                    //启动连接线程
                    new Thread(){
                        public void run(){
                            try {
                                InetAddress ipAdress = InetAddress.getByName("192.168.4.1");
                                if (sock == null) {
                                    sock = new Socket(ipAdress, 7000);
                                    isConnect = false;
                                    ConnectButton.setText("断开");
                                    stimButton.setEnabled(true);
                                }

                                status.setText("状态:连接成功，设置参数后点击刺激按钮");
                            } catch(Exception e) {
                                status.setText("状态:连接失败，请查看是否连接局域网");
                            }
                        }
                    }.start();
                }
                else{
                    try {
                        sock.close();
                        ConnectButton.setText("断开");
                        isConnect=true;
                        stimButton.setEnabled(false);
                    } catch (Exception e) {
                        status.setText("出现错误");
                    }
                }
            }
        });

        stimButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isStim) {
                    if (channel1.isChecked()){
                        channelSelction=1;
                    }else{
                        channelSelction=2;
                    }
                    String mA = mANum.getText().toString();
                    try {
                        DataInputStream input = new DataInputStream(sock.getInputStream());
                        DataOutputStream out = new DataOutputStream(sock.getOutputStream());
                        out.writeUTF("S");
                        String str="$"+"D"+Integer.toString(channelSelction)+mA+"*";
                        out.writeUTF(str);
                        input.readUTF();
                        isStim=false;
                    } catch (IOException e) {
                        status.setText("出现错误");
                    }
                } else {
                    try {
                        DataOutputStream stopStr = new DataOutputStream(sock.getOutputStream());
                        stopStr.writeUTF("P");
                    } catch (IOException e) {
                        status.setText("出现错误");
                    }
                }
            }
        });
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "Main Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app deep link URI is correct.
                Uri.parse("android-app://com.stimulaltor.taoxuewen.stimualtor/http/host/path")
        );
        AppIndex.AppIndexApi.start(client, viewAction);
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "Main Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app deep link URI is correct.
                Uri.parse("android-app://com.stimulaltor.taoxuewen.stimualtor/http/host/path")
        );
        AppIndex.AppIndexApi.end(client, viewAction);
        client.disconnect();
    }
}
