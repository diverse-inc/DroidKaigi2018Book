= Flutterでクロスプラットフォームの夢を見てみた

== Flutter とは？
iOS/Androidのクラスプラットフォーム開発を実現することができるGoogle発のフレームワークです。@<br>{}
言語としてはDart(生きとったんかワレ)で記述していきます。

== IntelliJ IDEにPluginを追加する
IntelliJにはFlutter用の便利なプラグインが存在するため、そちらを設定します。

==== Flutterプラグインの導入手順
まずIntelliJを起動してPreferences > Plugins > "Browse repositories…" を選択します。
入力欄に 'Flutter' と入力してFlutterプラグインをインストールします。

==== Flutter SDKの導入
Flutterで開発するためにはSDKが必要となります。
本来であればコマンドで行うところですが、前述のFlutterプラグインであればGUI上でインストール可能です。

IntelliJを再起動して"Create New Project"を選択します。
Flutterを選択するとSDKのパスの入力欄があり、その下の"Install SDK..."を選択します。
ディレクトリ選択のダイアログが表示されるので、SDKをインストールしたい場所を選択します。
選択後はSDKのダウンロード、初期設定が行われるので完了を待つだけです。

== try Flutter
開発環境が整ったのでいよいよFlutterに触れていきます。
といっても、Dart/Flutter初心者なので、簡単な通信を行うアプリを作っていきます。
ここではDroidKaigiのjsonを取ってきてセッション一覧を画面上に表示するものを作ります。

=== 新規プロジェクトの作成
入力必須の欄を埋めていきます。
注意することは、Javaのパッケージとして利用されるOrganizationには "-(ハイフン)" を含むと駄目ということくらいです。

@<icon>{samukei_01}

=== JSONの取得の実装
Dartではasync/awaitがあるので活用していきます。
通信はJavaScriptのPromiseっぽく受けることができたので、そちらに合わせました。

//list[main1][main1()][c]{
//}

=== レスポンスを受けるデータ型の実装
Dart Conf Appを参考にJSONのレスポンスを受けるデータ型を実装していきます。

//list[main2][main2()][c]{
//}

//memo{
Dartには "source_gen" というデータ型のシリアライザ／デシリアライザを自動生成するライブラリもあります。
規模的にも導入、学習コストのほうがかかりそうだったので、今回は利用しませんでした。
//}

=== 画面の実装
今回はListViewを使ってレイアウトを構成していきます。

//list[main3][main3()][c]{
//}

=== 完成したスクショ

== try Flutterで感じたこと
 * 導入はかなり簡単で単純なUIならiOS/Androidのクロスプラットフォームでパワーを発揮しそう。ただ、UIを凝ろうとするとつらそう。
 * Dart初心者すぎてわからないことが多かったが、Dart／Flutterの公式サイトのドキュメントが充実していて、ドキュメント読めば良いので助かった。
 * 文法でいうと、Kotlinよりもモダンではないので、今後に期待。
