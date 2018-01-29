= Androidアプリへの組み込み
https://github.com/dialogflow/dialogflow-android-client
dialogflowのクライアントがあるのでこちらを使います。

//source[AndroidManifest.xmlにパーミッション追加]{
<uses-permission android:name=“android.permission.INTERNET”/>
<uses-permission android:name=“android.permission.RECORD_AUDIO” />
//}
音声入力を使うのでこちらのパーミッションを追加しましょう。

//source[build.gradleに追加するものたち]{
implementation ‘ai.api:sdk:2.0.7@aar’
implementation ‘ai.api:libai:1.6.12’
//}
ほぼほぼai.apiがなんとかしてくれます。すごい。

//source[初期化処理など MainActivity.java]{
final AIConfiguration config = new AIConfiguration(CLIENT_ACCESS_TOKEN,
    AIConfiguration.SupportedLanguages.Japanese,
    AIConfiguration.RecognitionEngine.System);
    final AIDataService aiDataService = new AIDataService(config);
//}
サポート言語を日本語に変更するのを忘れないようにしましょう。

あとはaiListenerを追加し、API通信後に表示の制御を行っていきます。@<br>{}
dialogflow-android-client( https://github.com/dialogflow/dialogflow-android-client)に書いてあるので興味があれば是非ごらんください。

あとは主要なものをいくつかご紹介します
==== マイクからのリスニングを開始する
 * AIService.startListening()
==== リスニングを停止してAPI.AIを使って結果を送信する
 * aiService.stopListening();
==== API.AIサービスにリクエストを送らずにキャンセルする
 * aiService.cancel();

問題なくリスニングを処理できた場合には
AIService.onResultに値が戻ってくるのでアクションとパラメータをそこから取得することができます
//source[MainActivity.java]{
        public void onResult(final AIResponse response) {
        Log.i(TAG, "Action: " + result.getAction());
//}

 *自分が聞いた内容は
 ** response.getResult().resolvedQuery
 * その回答は
 ** response.getResult().getFulfillment().getSpeech();
戻ってきた値をTextViewなりListViewなりに表示したりなんなりしてください。

== まとめ
　最初の「OK Google、渋谷駅いきたい」は「OK Google、地図アプリでここから渋谷駅までのルートを調べて」@<br>{}
とかにしてあげるとスムーズに呼び出せるんだなぁ理解することができました。@<br>{}
使う側が呼び出す呪文を理解してあげないといけない所にハードルの高さを感じました。@<br>{}
あと少しの痒い所に手が届くと、生活のインフラとして使っていくことになるのかもしれません。@<br>{}
　コードに触れた分、少しほんの少しだけGoogleアシスタントと仲良くなれました。@<br>{}
ぼくはこの冬ついにAndroidからiPhoneに機種変しました。Hey Siri!!!
