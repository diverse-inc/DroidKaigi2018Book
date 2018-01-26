== 試して感じたこと

2018年1月末現在（原稿執筆当時）、おそらくDroidKaigi2018iOSを超える規模のKotlin/Nativeで作られたiOSアプリの事例は国内では存在しないと思います。
今後Kotlin/Nativeを採用しようと考えておられる皆様の参考になれば良いなと思います。


=== CLionのKotlin/Native pluginはまだ完成度が低い


Kotlin/Native開発において、IDEはCLion@<fn>{clion}を使います。CLion向けにKotlin/Nativeのプラグインが提供されているので、それをインストールしておきましょう。
//footnote[clion][@<href>{https://www.jetbrains.com/clion/}]

これだけで、Kotlin/Androidとあまり変わらない操作感でiOSの開発をすることができます。なんて便利！

しかしまだ開発途上なのか、未完成だと思える点も多く見受けられます。
だから駄目、という訳ではありません。シンタックスハイライトなどは問題なく機能しますし、無いより100倍マシです。これらの点が解消されたら、きっと誰でも簡単にKotlin/Native開発に参入できるようになるでしょう。というくらいです。


以下、全てKotlin/Native pluginバージョン 0.1-dev-86 時点でのお話です。

==== 補完が遅い

開発にはMacBook Pro (late 2016, Core i7 2.9GHz, メモリ16GB)を使用しました。MacBookの中ではハイスペックなマシンのはずです。
このマシンパワーでもってしても、オブジェクトのフィールド名の補完に2秒くらいかかります。しかも補完候補を出すために画面描画が止まります。カーソルも進みません。2秒あればフィールド名くらい打ち終えられるので、AndroidStudioの補完速度に慣れてしまっているとストレスの元になるかもしれません。


==== Quick Fixでimportしてくれない

Xcodeが抱えているSDKのAPIは@<code>{platform}パッケージ以下に配置されています。
例えばFoundation.frameworkのAPIは@<code>{platform.Foundation}を、UIKit.frameworkのAPIは@<code>{platform.UIKit}をimportすることで使用できるようになります。

Kotlin/Androidの感覚では、importせずにクラス名をコード中に記述した場合、Quick Fixでimport文を追加する事ができます。しかし現在のKotlin/Nativeプラグインでは、まだこの操作ができません。
kotlinxパッケージ以下の拡張関数についてはQuick Fixのバルーンが表示されるので、全くできないというわけではないようですが。


==== 一部のplatformパッケージ以下の宣言にコードジャンプできない

例えば@<code>{UITableView}などの宣言がどのような形になっているのか見てみたいとしましょう。
Kotlin/Andoridの感覚であればCmd + BやCmd + クリックで宣言へジャンプすると思います。
しかし一部のplatform以下のパッケージには"Cannot find declaration to go"と言われてジャンプできません。
手元で試したところ、@<code>{platform.UIKit}以下や@<code>{platform.Foundation}以下のAPIにはジャンプできず、@<code>{platform.darwin}以下のAPIにはジャンプできました。

コードジャンプはできませんが、@<code>{platform.UIKit}の宣言は ~/.konan/kotlin-native-macos-0.5/klib/platform/iphone/UIKit/linkata/package_platform.UIKit.knm で見ることができました。プラットフォームやバージョンによっては別の場所に置かれている可能性もあるので、適宜読み替えてください。


=== IDEと統合されたデバッガが欲しい

Kotlin/NativeでのiOS開発の場合、CLionでコードを書き、Xcodeでビルドを走らせます。現時点ではCLion（Kotlin/Native plugin）にはiOSアプリのパッケージを作る機能がないためです。

すると問題になるのはブレークポイントの挿入です。
CLionからiPhoneで動いているプロセスへのアタッチはできないようですし、XcodeはKotlinのコードにブレークポイントを置くことはできません。
一応Xcodeからlldbをアタッチすることはできるので、インスタンスのアドレスがわかっていれば、オブジェクトの状態を変更したりすることは可能そうです。
それはそれで大変なので、現状はprintfデバッグで乗り切っています。

GUIからのブレークポイント操作に慣れきってしまったゆとり世代の私としては、CLionからデバッグできるようになることを期待したいと思います。


=== Kotlinのstdlibの機能を使用できるので捗る

ネガティブな感想が続きましたが、ポジティブな感想もあります。

Kotlin/Androidの利点の一つでもあるのですが、Kotlinは言語機能と一緒に提供されるKotlin Standerd Library (kotlin-stdlib)があり、しかも使い勝手が良いのです。私は特にコレクション周りの拡張関数（@<code>{map}や@<code>{find}など）に頼り切って生きています。
Kotlin/Nativeでもこれらが使用可能です。
今回のDroidKaigi2018アプリでも、セッションの一覧を開始時刻ごとに分けるところなどで大いに使用しています。

//list[kotlinstdlib][src/main/kotlin/sessionslist/SessionsDataSource.kt を一部改変][kt]{
private val groupedSessions: List<Pair<Date, List<Session>>> =
        initialSessions  // List<Session>
            .groupBy { it.startTime }
            .toList()
            .sortedBy { it.first.getTime().toLong() }
//}

同じことはSwiftでもできるのでしょうが、私のSwift習熟度では、どう書けば良いのかぱっと思いつきません。
もし現在のAndroidアプリと同じくらいの簡単さでKotlin/Nativeを使用したiOSアプリ開発を始めることができるならば、Kotlinに慣れたエンジニアはKotlin/Nativeを使用したほうが圧倒的に高い生産性を発揮できるでしょう。

