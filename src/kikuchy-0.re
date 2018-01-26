= Kotlin/NativeでDroidKaigiアプリのiOS版を作ってみた

作ってみました。

https://github.com/kikuchy/DroidKaigi2018iOS


== 経緯

Androidアプリ開発の際、弊社ではKotlinを開発言語とすることが増えてきました。
かくいう私もKotlin大好きなエンジニアの一人。というかKotlinを一番最初に導入した張本人でもあります（まだStableではなかった、M13くらいのときに入れました！）。

近年、Kotlin/Nativeが公表され、iOSやWebAssemblyの開発にもKotlinを使用できる兆しが見えてきています。もしこれが広く使われるようになれば、Kotlinだけでスマートフォンアプリ、Webのフロント、サーバサイド、果ては組み込みプログラムまで書けてしまうことになります。激アツですね！

弊社ではAndroidアプリだけでなくiOSアプリも作成しているので、Kotlin/Nativeがどれくらい実用的なのか興味があります。
しかし、現行のアプリは大抵Swiftで書かれているため、今からKotlin/Nativeを入れるのは敷居が高そうです。

ところで、前年のDroidKaigi2017ではiOS版のアプリが突貫で開発される@<fn>{droidkaigi2017ios}、という事がありました。
//footnote[droidkaigi2017ios][https://github.com/kishikawakatsumi/DroidKaigi]
DroidKaigi参加者の中にはAndroidがメイン機ではない人も多く、そのためiOS版が望まれてのことでした。
実は私もAndroidエンジニアのくせにSIMの刺さったAndroid機を持っておらず、通信を伴う作業は全てiPhoneに任せっきりです。
DroidKaigi運営の皆様もその点を把握しておられるようで、今年のDroidKaigiアプリのリポジトリにも「iOS版を開発する」というissueが立てられていました。@<fn>{iosissue}
//footnote[iosissue][https://github.com/DroidKaigi/conference-app-2018/issues/66]

Kotlin/NativeでiOS開発を試したい！
私もiOS版のDroidKaigiアプリが欲しい！

ということで、DroidKaigi2018iOSリポジトリが爆誕したのでした。


== お伝えすること

ここでは、以下のことをお伝えし、またお伝えしません。

* お伝えすること
** 試して感じたこと
** Kotlin/Native iOS開発でハマりやすいところ
* お伝えしないこと
** 開発の初め方（良い記事があるのでそちらを御覧ください@<fn>{startguid1}@<fn>{startguid2}）
** iOS開発の知識
//footnote[startguid1][https://qiita.com/noripi/items/4ee969c48b3da5ca6fbd]
//footnote[startguid2][https://qiita.com/oboenikui/items/07481c6f44fe3e2c4440]
