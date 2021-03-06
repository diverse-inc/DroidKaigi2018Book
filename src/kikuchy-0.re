= Kotlin/NativeでDroidKaigiアプリのiOS版を作ってみた

//lead{
作ってみました。

@<href>{https://github.com/kikuchy/DroidKaigi2018iOS}
//}


== 書いている人

Twitter: @<href>{https://twitter.com/kikuchy, @kikuchy}

今回のDroidKaigiには3本のCfPを提出して全部落ちました。

== 経緯

Androidアプリ開発の際、弊社ではKotlinを開発言語とすることが増えてきました。
かくいう私もKotlin大好きなエンジニアの一人。というかKotlinを一番最初にプロダクトに導入した張本人でもあります（まだStableではなかった、M13くらいのときに入れました！）。

近年、Kotlin/Nativeが公表され、iOSやWebAssemblyの開発にもKotlinを使用できる兆しが見えてきています。もしこれが広く使われるようになれば、Kotlinだけでスマートフォンアプリ、Webのフロント、サーバサイド、果ては組み込みプログラムまで書けてしまうことになります。激アツですね！

弊社ではAndroidアプリだけでなくiOSアプリも作成しているので、Kotlin/Nativeがどれくらい実用的なのか興味があります。
しかし、現行のアプリは大抵Swiftで書かれているため、今からKotlin/Nativeを入れるのは敷居が高そうです。

ところで、前年のDroidKaigi2017ではiOS版のアプリが突貫で開発される@<fn>{droidkaigi2017ios}、という事がありました。
//footnote[droidkaigi2017ios][@<href>{https://github.com/kishikawakatsumi/DroidKaigi}]
DroidKaigi参加者の中にはAndroidがメイン機ではない人も多く、そのためiOS版が望まれてのことでした。
実は私もAndroidエンジニアのくせにSIMの刺さったAndroid機を持っておらず、通信を伴う作業は全てiPhoneに任せっきりです。
DroidKaigi運営の皆様もその点を把握しておられるようで、今年のDroidKaigiアプリのリポジトリにも「iOS版を開発する」というissueが立てられていました。@<fn>{iosissue}
//footnote[iosissue][@<href>{https://github.com/DroidKaigi/conference-app-2018/issues/66}]


Kotlin/NativeでiOS開発を試したい！

私もiOS版のDroidKaigiアプリが欲しい！

おっ、なんだか都合の良い組み合わせ！！


ということで、DroidKaigi2018iOSリポジトリが爆誕したのでした。

#@# 締め切りまでに見た目が整えば、iOSクライアントのスクショを入れる


== お伝えすること

ここでは、以下のことをお伝えし、またお伝えしません。

 * お伝えすること
 ** 試して感じたこと
 ** Kotlin/Native iOS開発でハマりやすいところ
 * お伝えしないこと
 ** 開発の初め方（良い記事があるのでそちらを御覧ください@<fn>{startguid1}@<fn>{startguid2}）
 ** iOS開発の知識 
 ** Kotlin/Nativeの基本的なところ
 
//footnote[startguid1][@<href>{https://qiita.com/noripi/items/4ee969c48b3da5ca6fbd}]
//footnote[startguid2][@<href>{https://qiita.com/oboenikui/items/07481c6f44fe3e2c4440}]


== 著者スペック

DroidKaigi2018iOSリポジトリを作った時点、つまり開発を始めた時点でのスペックです。

 * Kotlin歴2年弱
 * Android開発歴2年くらい
 * iOS開発歴1年くらい（Objective-C, Swift, Titaniumでの歴の合計）
 * Kotlin/Native歴1日弱
 