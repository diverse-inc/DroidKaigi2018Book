= Kotlin/Native iOS開発でハマりやすいところ

実際にハマって解決したことを共有します。
Kotlin/Nativeに挑戦されるみなさまがこうしたところを踏み抜かぬよう…


== FoundationだけimportしてもNSIndexPathのrowやselctionを参照できない

@<code>{UITableView}（Androidの@<code>{ListView}や@<code>{RecyclerView}に相当）を扱う場合、@<code>{NSIndexPath}@<fn>{aboutNSIndexPath}は避けて通れません。
//footnote[aboutNSIndexPath][@<code>{UITableView}は大枠としてセクション、その中に各行を抱えています。作成しようとしているセルはどのセクションのどの行なのか、などを表現するために@<code>{NSIndexPath}という入れ子になった配列のどこにデータがあるのかを示すための専用クラスが用意されています。]

@<code>{NSIndexPath}は@<code>{Foundation}で実装されているクラスです。使用する際は
@<br>{}@<code>{platform.Foundation.NSIndexPath}をimportします。

その状態でメンバの@<code>{section}や@<code>{row}を参照しようとすると、なんとコンパイルエラーに。補完候補にも表示されません。
Foundationのドキュメント@<fn>{NSIndexPathDoc}には@<code>{section}も@<code>{row}も記述があるのに、なぜ！？
//footnote[NSIndexPathDoc][@<href>{https://developer.apple.com/documentation/foundation/nsindexpath?language=objc}]

実は@<code>{section}と@<code>{row}はFoundationではなくUIKitで宣言されている拡張メンバ@<fn>{declarationOfRow}なのです。
そのため、@<code>{platform.UIKit.section}や@<code>{platform.UIKit.row}をimportしないと使用できません。
//footnote[declarationOfRow][UIKitの@<code>{NSIndexPath+UIKitAdditions.h}に宣言があります。実はドキュメントの中ほど『Using Special Node Names』の見出しには『UIKitとAppKitが、index pathのうち1段目と2段目にアクセスするための便利な名前を提供しているよ』と、ヒントらしきことが書いてある…]

私が遭遇したのはNSIndexPathの例のみですが、他にもこのようにパッケージをまたいで宣言されている拡張メンバやメソッドがあるかもしれません。
ドキュメントには大元の宣言があるパッケージに記載されているものもあるので、「おかしいな」と思ったら、Objective-Cでコードを書いて、宣言元にジャンプしてどのパッケージに所属するものなのかを確認したほうが良さそうです。あとドキュメントをちゃんと読みましょう。

または初めから、@<code>{platform.Foundation.*}と@<code>{platform.UIKit.*}をimportしておいてしまうとかでも良いかもですね。


== 構造体がCValue<T>でやってくるので扱いに困る

Objective-CやSwiftにはあってKotlinに無いものの一つが、構造体です。

Kotlin/Nativeでは、構造体はメンバ変数を@<code>{var}で保持している、@<code>{CStructVar}を継承したクラスとして扱われます。
なんと簡単に扱えるのでしょう！　と思っていたらそうではない箇所が……

@<code>{UITableView.contentInset}から@<code>{UIEdgeInsets}構造体を取り出して触ろうとしたら、@<code>{CValue<UIEdgeInsets>}型の値が返ってくるではありませんか！
え、@<code>{CValue<T>}って何…？


実はCの関数の引数/戻り値として構造体を使用する場合は、@<code>{CValue<T>}型の値として扱われます。
@<code>{CValue<T>}型は公式のドキュメントでも言われているとおり不明瞭な型で、当然ながらこのままでは構造体のメンバにアクセスすることはできません。
中の構造体に触るには@<code>{useContents()}などを使用する必要があります。

きちんと調べていないのですが、これはおそらくKotlin/Nativeでのclassのメモリ内での扱い方が、Cの構造体の扱いと違うところから来ているのだと思います。
Kotlinのclassのインスタンスはプラットフォームによって管理の仕方を変えることができるようになる計画があるようですから、Cで値型として扱われる構造体とは管理の仕方が異なることは想像できます。

iOS開発においては@<code>{CGRect}や@<code>{UIEdgeInsets}などは作成専用の関数、@<code>{CGRectMake}や@<code>{UIEdgeInsetsMake}などがあるので、こちらを使用しましょう。これらの関数も構造体を@<code>{CValue<T>}型として返してくれるので、型合わせパズルに苦しまずに済みます。


== uncheckedCastが必要になる箇所がてんこ盛り＆変な型にキャストしてもprintln()ではおかしくなっていることに気づきにくい

@<code>{NSDictionary}（Java/KotlinのMapのようなもの）から値を取り出す際は必ず@<code>{uncheckedCast()}によるダウンキャストが必要になります。これはNSDictionaryが保持している値を@<code>{id}型（JavaのObject型のようなもの）として返してくるためです。

DroidKaigi2018iOSでは、JSONのパースに@<code>{NSJSONSerialization}を使用しています。パースされたデータは@<code>{NSDictionary}や@<code>{NSArray}として返ってくるので、ここから値を適宜取り出してゆく必要があります。

その際に間違った型にキャストしてしまうと、面白い事が起こります。


本来はNSNumber型（オブジェクト）として取り出さなければいけない値をNSInteger（Cのlongのエイリアス、つまりプリミティブ型！ KotlinのLong型にマップされる）として取り出してしまった際に起きたことです。

//list[misscast][間違えたキャストをした場合][kt]{
// json = { key: 1234 }
val value: Long = json.valueForKey("key").uncheckedCast()

println(value)             // 1234
println(value == 1234L)    // false
//}

println()の結果は期待通りなのに、比較の結果は偽になりました。

C言語をわかってらっしゃる方はもうおわかりだと思います。
取得できたvalueはポインタです。
当然、期待していた数値と比較してもfalseを返すでしょう。

Objective-Cのラインタイムにおいて、クラスとはCの構造体のポインタで、メソッド呼び出しは関数に構造体のポインタを渡すことです。
調査していないのですが、おそらくNSObjectを継承したクラスに対してKotlinからtoString()を呼び出すと、内部でNSObjectのdescriptionメソッドを呼び出すのだと思います。
キャストが失敗していてもtoString()は適切に呼び出され、表示上は期待通りになってしまう…おそらくこんなからくりがあるのではないかと思います。

とりあえず、「NSDictionaryにはオブジェクト型しか格納できない」「NSIntegerはオブジェクトではない」ということは注意しましょう。
Objective-Cをやっていればわかる、かなり初歩的な間違いではあるのですが…

