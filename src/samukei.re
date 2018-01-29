= Flutterでクロスプラットフォームの夢を見てみた

== Flutter とは？
iOS/Androidのクラスプラットフォーム開発を実現することができるGoogle発のフレームワークです。
言語としてはDart(生きとったんかワレ)で記述していきます。

== IntelliJ IDEにPluginを追加する
IntelliJにはFlutter用の便利なプラグインが存在するため、そちらを設定します。

==== Flutterプラグインの導入手順
まずIntelliJを起動してPreferences > Plugins > "Browse repositories…" を選択します。
表示された画面で 'Flutter' と入力してFlutterプラグインをインストールします。

==== Flutter SDKの導入
Flutterで開発するためにはSDKが必要となります。
本来であればコマンドで行うところですが、前述のFlutterプラグインであればGUI上でインストール可能です。@<br>{}

===== IntelliJ上でのインストール手順
 1. IntelliJを再起動して"Create New Project"を選択します。
 2. Flutterを選択するとSDKのパスの入力欄があり、その下の"Install SDK..."を選択します。
 3. ディレクトリ選択のダイアログが表示されるので、SDKをインストールしたい場所を選択します。
 4. 選択後はSDKのダウンロード、初期設定が行われるので完了を待つだけです。

== try Flutter
開発環境が整ったのでいよいよFlutterに触れていきます。
といっても、Dart/Flutter初心者なので、簡単な通信を行うアプリを作っていきます。
ここではDroidKaigiのjsonを取ってきてセッション一覧を画面上に表示するものを作ります。@<br>{}
なお、今回のソースコードはリポジトリに公開しています。@<fn>{github}

=== 新規プロジェクトの作成
入力必須の欄を埋めていきます。
注意することは、Javaのパッケージとして利用されるOrganizationには "-(ハイフン)" を含むと駄目ということくらいです。@<br>{}
作成されたプロジェクトにはサンプルコードが含まれているので、こちらをベースに実装すると楽に始められます。

//image[NewProject][新規プロジェクト][scale=0.40]{
//}


=== JSONの取得の実装
Dartではasync/awaitがあるので活用していきます。
通信はJavaScriptのPromiseっぽく受けることができたので、そちらに合わせました。

//list[main1][class DroidKaigiApi#getSessions][Dart]{
// 非同期処理が完了した際に返すデータをFuture<T>で表す
static Future<Sessions> getSessions() async { // async
  var completer = new Completer();

  final uri = Uri.parse(_baseUrl + "sessionize/all.json");
  // awaitで非同期処理
  await new HttpClient().getUrl(uri)
      .then((request) => request.close())
      .then((response) {
        if (response.statusCode == HttpStatus.OK) {
          var result = "";
          // レスポンスをUTF8変換
          response.transform(UTF8.decoder).listen((contents) {
            result += contents;
          })
          // 1. レスポンス(UTF8)をJSON変換する
          // 2. JSONをSessionにパースする
          // 3. Completerの処理を完了させる。
          .onDone(() => completer.complete(Sessions.parse(JSON.decode(result))));
        }
      })
      .catchError((e) {
    print(e);
  });
  // CompleterのFutureを返却
  return completer.future;
}
//}

=== レスポンスを受けるデータ型の実装
Dart Conf Appを参考にJSONのレスポンスを受けるデータ型を実装していきます。

//list[response][class Room][Dart]{
class Room {
  final int id;
  final String name;
  final int sort;

  // JSONのパース
  static Room parse(dynamic json) {
    return new Room(
      id: json['id'],
      name: json['name'],
      sort: json['sort']
    );
  }

  // コンストラクタ
  Room({
    this.id,
    this.name,
    this.sort
  });
}
//}

//memo[一言メモ]{
Dartには "source_gen" というデータ型のシリアライザ／デシリアライザを自動生成するライブラリもありますが、
規模的にも導入、学習コストのほうがかかりそうだったので、今回は利用しませんでした。
//}

=== 画面の実装
UIはWidgetとWidgetの状態から構築されます。
今回はSessionを表示するので、SessionのWidget、Stateを定義します。

//list[StatefulWidget][class SessionsPage][Dart]{
class SessionsPage extends StatefulWidget {
  // 状態
  @override
  _SessionsPageState createState() => new _SessionsPageState();
}

// 状態は同じファイルで定義したため、Private指定
class _SessionsPageState extends State<SessionsPage> {
}
//}

Flutterではレイアウト用のxmlなどではなく、Viewの構築はコードで行っています。
今回はセクションの一覧を表示するので、ListViewを作成します。
なお、一部省略していますので、全体はリポジトリを参照ください。@<fn>{github}

//list[State][class _SessionsPageState][Dart]{
class _SessionsPageState extends State<SessionsPage> {

  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        // ナビゲーションエリアのタイトル指定
        title: new Text(widget.title),
      ),
      body: new FutureBuilder<Sessions>(
          // futureを待ち受け
          future: DroidKaigiApi.getSessions(),
          builder: (BuildContext context, AsyncSnapshot<Sessions> snapshot) {
            if (!snapshot.hasData) {
              // データ無ければ空表示
              return new Container();
            }

            // 略(StatelessWidgetのListを生成する)

            // ListViewの生成
            return new ListView.builder(
                padding: new EdgeInsets.all(8.0),
                itemCount: items.length,
                itemBuilder: (BuildContext context, int index) => items[index]
            );
          }
      ),
    );
  }
}
//}

=== 完成したアプリのスクリーンショット
リポジトリのプロジェクトを実行するとこのように動作します。@<fn>{github}

//image[AppScreenshot][スクリーンショット][scale=0.40]{
//}

== try Flutterで感じたこと
 * 導入はかなり簡単で単純なUIならiOS/Androidのクロスプラットフォームでパワーを発揮しそう。ただ、UIを凝ろうとするとつらそう。
 * Dart初心者すぎてわからないことが多かったが、Dart／Flutterの公式サイトのドキュメントが充実していて、ドキュメント読めば良いので助かった。
 * 文法でいうと、Kotlinよりもモダンではないので、今後に期待。
 * 実行時エラーが起きるとアプリ内の背景が真っ赤になり、ちょっとしたスリルを味わえる。

//image[RunTimeError][(おまけ)スリルのある実行時エラー][scale=0.40]{
//}

//footnote[github][公開リポジトリ: https://github.com/SAMUKEI/flutter_droidkaigi2018]
