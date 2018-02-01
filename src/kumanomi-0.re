= どうやってGoogleアシスタントを自作のアプリから呼び出すの？

=== 「OK Google、渋谷駅いきたい」
私は一度もこの機能を使ったことがありません。恥ずかしいからです。@<br>{}
使ったこともなければ興味もなく業務で使う予定もないのでちょこっと共有させていただきます。

=== 書いてる人
kumanomi

PoiboyのAndroidエンジニアをしてます

== Googleアシスタントで検索してすぐに出てくる謎の単語たちを1行でご紹介します。
 * 「Google Assistant」
 ** 「OK Google」で呼び出される人
 * 「Actions on Google」
 ** Google Assistantから呼び出すことのできる人
 * 「Dialogflow」
 ** 言葉を解析してくれる人
 * 「Server (Firebase、Heroku...etc)」
 ** Dialogflowで解析した言葉を処理するためのServer

//memo[大雑把な流れ]{
ぼく(すっごい命令) -> GoogleAssistant -> Action on Google ->

Dialogflow -> すっごい命令実行される
//}

== Action on Googleでの呼び出し方法は2通り
 * 「Explicit Invocation」 (明示的な呼び出し)
 ** (例) 「OK Google、ほげほげアプリですごいことさせて」
 ** (例) 「OK Google、二郎でニンニクマシマシヤサイアブラカラメで」
 * 「Implicit Invocation」 (暗黙的な呼び出し)
 ** (例) 「OK Google、ほげほげしたい」
 ** (例) 「OK Google、ラーメン食べたい」

== Action on Googleで作成できるアクションも2通り
 * Direct Action
 ** 機器を操作するアクション
 * Conversation Action
 ** チャットボットの開発を可能にする対話型アクション

今回は「Conversation Action」を試していきます。

== Dialogflowで単語登録

チャットボット用の返信してくれる文言などを登録していきます。ここでもまた新しい単語が出てくるのでご紹介します。

 * Intent
 ** AndroidでおなじみのIntentです。ここでは「Aと言われたらBする」のようなものを設定できるものです。
 * Entities
 ** 言葉の呼び方を定義できます。
 ** 「こんばんは」や「おばんです」などの同じ意味でも違う言い方の言葉を1まとめに定義することができます。
 * Fulfillment
 ** Webhookなどをして回答結果を返してあげるのに使うようです。

Dialogflowにgoogleアカウントで登録し、Agent(プロジェクトのようなもの)を作成します。

//image[kumanomi-screenshot1][質問][scale=1]{
//}

//image[kumanomi-screenshot2][答え][scale=1]{
//}

更にIntentを登録しTOP画面の歯車アイコンからClientAccessTokenを取得します。@<br>{}
これは後ほどAndroidアプリ実装の際につかうことになります。

== Androidアプリへの組み込み
dialogflowのクライアントが@<href>{https://github.com/dialogflow/dialogflow-android-client, github上}にあるのでこちらを使います。

==== 音声入力を使うのでこちらのパーミッションを追加しましょう
//source[AndroidManifest.xml]{
<uses-permission android:name=“android.permission.INTERNET”/>
<uses-permission android:name=“android.permission.RECORD_AUDIO” />
//}

==== ほぼai.apiがなんとかしてくれます。すごい！
//source[build.gradle]{
implementation ‘ai.api:sdk:2.0.7@aar’
implementation ‘ai.api:libai:1.6.12’
//}

==== 初期化など
先ほどDialogflowで取得したClientAccessTokenはここで使います。@<br>{}
サポート言語を日本語に変更するのを忘れないようにしましょう。
//source[MainActivity.java]{
final AIConfiguration config = new AIConfiguration(CLIENT_ACCESS_TOKEN,
    AIConfiguration.SupportedLanguages.Japanese,
    AIConfiguration.RecognitionEngine.System);
    final AIDataService aiDataService = new AIDataService(config);
//}

aiListenerを追加し、API通信後に表示の制御を行っていきます。

この辺は@<href>{https://github.com/dialogflow/dialogflow-android-client, dialogflow-android-client}に書いてあるので興味があれば是非ごらんください。

==== 主要なものをいくつかご紹介します。

 * マイクからのリスニングを開始する
 ** AIService.startListening()
 * リスニングを停止してAPI.AIを使って結果を送信する
 ** aiService.stopListening();
 * API.AIサービスにリクエストを送らずにキャンセルする
 ** aiService.cancel();

問題なくリスニングを処理できた場合には
AIService.onResultに値が戻ってくるのでアクションとパラメータをそこから取得することができます。
//source[MainActivity.java]{
        public void onResult(final AIResponse response) {
        Log.i(TAG, "Action: " + result.getAction());
//}
 * 自分が聞いた内容
 ** response.getResult().resolvedQuery
 * そしてその回答
 ** response.getResult().getFulfillment().getSpeech();
あとは戻ってきた値をTextViewなりListViewなりに表示したりなんなりしてください。

== まとめ
　最初の「OK Google、渋谷駅いきたい」は「OK Google、地図アプリでほげほげから渋谷駅までのルートを調べて」
とかにしてあげるとスムーズに呼び出せるんだなぁ理解することができました。@<br>{}
使う側が呼び出す呪文を理解してあげないといけない所にハードルの高さを感じました。@<br>{}
あと少しの痒い所に手が届くと、生活のインフラとして使っていくことになるのかもしれません。@<br>{}
　コードに触れた分、少しほんの少しだけGoogleアシスタントと仲良くなれました。@<br>{}
ぼくはこの冬ついにAndroidからiPhoneに機種変しました。Hey Siri!!!
