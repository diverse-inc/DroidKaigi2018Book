= Googleアシスタント対応アプリってどうやってつくるの？

== 「OK Google、渋谷駅いきたい」
私は一度もこの機能を使ったことがありません。恥ずかしいからです。@<br>{}
使ったこともなければ興味もなく業務で今後使う予定もないので是非今回共有させていただきます。

== 書いてる人
kumanomi@<br>{}
たまねぎ剣士になりたい


== すぐに出てくる謎の単語たち
調べてすぐに出てくる重要そうな単語を1行でご紹介します。
==== 「Google Assistant」
 * 「OK Google」で呼び出される人
==== 「Actions on Google」
 * Google Assistantから呼び出すことのできる人
==== 「Dialogflow」
 * 言葉を解析してくれる人
==== 「Server (Firebase、Heroku...etc)」
 * Dialogflowで解析した言葉を処理するためのServer

ぼく(すっごい命令) -> GoogleAssistant -> Action on Google -> Dialogflow -> すっごい命令実行される
大雑把な処理の流れはこのようになります。


== Action on Googleでの呼び出し方法は2通り
==== 「Explicit Invocation」 (明示的な呼び出し)
 * (例) 「OK Google、ほげほげアプリですごいことさせて」
 * (例) 「OK Google、二郎でニンニクマシマシヤサイアブラカラメで」
==== 「Implicit Invocation」 (暗黙的な呼び出し)
 * (例) 「OK Google、ほげほげしたい」
 * (例) 「OK Google、ラーメン食べたい」

=== Action on Googleで作成できるアクションも2通り
==== Direct Action
 * 機器を操作するアクション
==== Conversation Action
 * 二つ目はチャットボットの開発を可能にする対話型アクション

今回は「Conversation Action」を試していきます。

== Dialogflowで単語登録
チャットボット用の返信してくれる文言などを登録していきます。また新しい単語が出てくるのでご紹介します。
==== Intent
 * AndroidでおなじみのIntentです。ここでは「Aと言われたらBする」のようなものを設定できるものです。
==== Entities
 * 言葉の呼び方を定義できます。
 *「こんばんは」や「おばんです」などの同じ意味でも違う言い方の言葉を1まとめに定義することができます。
==== Fulfillment
 * Webhookなどをして回答結果を返してあげるのに使うようです。

Dialogflowにgoogleアカウントで登録し、Agent作ります。Agentはプロジェクトのようなものです。@<br>{}
Agentを作成後にIntentを登録後に、TOP画面の歯車アイコンからClientAccessTokenを取得します。@<br>{}
これはAndroidアプリ実装の際につかうことになります。
