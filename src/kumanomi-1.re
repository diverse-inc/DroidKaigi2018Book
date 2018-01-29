= Googleアシスタント対応アプリってどうやってつくるの？

== Androidアプリへの組み込み
https://github.com/dialogflow/dialogflow-android-client
dialogflowのクライアントがあるのでこちらを使います。
    
=== パーミッションの追加
//list[main][AndroidManifest.xml][java]{
<uses-permission android:name=“android.permission.INTERNET”/>
<uses-permission android:name=“android.permission.RECORD_AUDIO” />
//}
音声入力を使うのでこちらのパーミッションを追加しましょう。
   
=== gradleに追加するものたち
//list[main][build.gradle][java]{
implementation ‘ai.api:sdk:2.0.7@aar’
implementation ‘ai.api:libai:1.6.12’
//}
ほぼほぼai.apiがなんとかしてくれます。すごい。
   
=== 初期化など
//list[main][MainActivity.java][java]{
final AIConfiguration config = new AIConfiguration(CLIENT_ACCESS_TOKEN, 
    AIConfiguration.SupportedLanguages.Japanese, 
    AIConfiguration.RecognitionEngine.System);
    final AIDataService aiDataService = new AIDataService(config);
//}
サポート言語を日本語に変更するのを忘れないようにしましょう。

あとはaiListenerを追加し、API通信後に表示の制御を行っていきます。
dialogflow-android-client( https://github.com/dialogflow/dialogflow-android-client)に書いてあるので興味があれば是非ごらんください。
    
あとは主要なものをいくつかご紹介します
 * マイクからのリスニングを開始する
 ** AIService.startListening()
 * リスニングを停止してAPI.AIを使って結果を送信する
 ** aiService.stopListening();
 * API.AIサービスにリクエストを送らずにキャンセルする
 ** aiService.cancel();

問題なくリスニングを処理できた場合には
AIService.onResultに値が戻ってくるのでアクションとパラメータをそこから取得することができます
//list[main][MainActivity.java][java]{
        public void onResult(final AIResponse response) {
        Log.i(TAG, "Action: " + result.getAction());
//}

 *自分が聞いた内容は
 ** response.getResult().resolvedQuery
 * その回答は
 ** response.getResult().getFulfillment().getSpeech();
戻ってきた値をTextViewなりListViewなりに表示したりなんなりしてください。
    
== 総括
　最初の「OK Google、渋谷駅いきたい」は「OK Google、地図アプリでここから渋谷駅までのルートを調べて」
とかにしてあげるとスムーズに呼び出せるんだなぁ理解することができました。
使う側が呼び出す呪文を理解してあげないといけない所にハードルの高さを感じました。
あと少しの痒い所に手が届くと、生活のインフラとして使っていくことになるのかもしれません。

コードに触れた分、少しほんの少しだけGoogleアシスタントと仲良くなれました。

ぼくはこの冬ついにAndroidからiPhoneに機種変しました。
Hey Siri!!!