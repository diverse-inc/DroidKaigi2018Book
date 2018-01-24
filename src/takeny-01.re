= OkHttp3+Retrofit2+Kotlin Coroutineでつくるnasneクライアント最初の一歩
//lead{
AndroidでHTTPによるAPI通信を行うときに使うライブラリは OkHttp3, Retrofit2そしてRxJavaの組み合わせが定番です。

しかしKotlin1.1からExperimentalではありますがCoroutineが搭載されました。Coroutineを使うことによってこれまでのコールバック地獄やRxのメソッドチェーンから解放され
直感的なコードで表現できるようになることでしょう。

またCoroutineはKotlin1.2でProduct Readyであることが宣言され、1.3ではいよいよExperimentalが外れる予定でとりあえず簡単な使い方を知って勉強し始めるにはちょうどいいタイミングかもしれません。

そこで本章では実例を使ったコルーチンの簡単な説明とnasneのAPIを叩いてハードウェア情報や内蔵HDDの情報を取得するクライアントアプリをOkHttp3+Retrofit2+Coroutineを使って作ってみた話を書きます。
//}

//footnote[nasne-r]["nasne(ナスネ)"は株式会社ソニー・インタラクティブエンタテインメントの登録商標または商標です。]

== コルーチンとは

一言でいえば「中断・再開可能な関数」です。これだけではわかりにくいですし、また詳しく説明するとそれだけで薄い本一冊書けてしまうレベルなので具体的な例でみてみましょう。

@<list>{api-connect-1}はAPIを叩いてnasneのハードウェア情報を取得し型番をトーストを使って表示するコードをOkHttpとRetrofitのみで実装したコードです。
コールバックで結果を受け取るという一般的な非同期処理における方法ですね。

//pagebreak

//list[api-connect-1][OkHttpとRetorfitのみで実装した通信部分][kotlin]{
api.getHardwareInfo().enqueue(object : Callback<Info> {
       override fun onResponse(call: Call<Info>, response: Response<Info>) {
           val info = response.body()
           val productName: String = (info?.productName) ?: "NULL"
           Toast.makeText(this@MainActivity, productName, Toast.LENGTH_LONG).show()
       }
       override fun onFailure(call: Call<Info>, t: Throwable) {
           Toast.makeText(this@MainActivity, "エラー", Toast.LENGTH_LONG).show()
       }
   })
//}

Rxを使うともうすこし簡単に書くことができますが、もっと簡単に、同期的に書くことができる方法があります。それがコルーチンです。

コルーチンを使うと@<list>{api-connect-2}のように書くことができます。

//list[api-connect-2][コルーチンを使った実装][kotlin]{
launch(UI) {
    try {
        val info = api.getHardwareInfo().await()
        Toast.makeText(this@MainActivity, info.productName, Toast.LENGTH_LONG).show()
    } catch(e: Exception) {
      Toast.makeText(this@MainActivity, "エラー", Toast.LENGTH_LONG).show()
    }
}
//}

コールバックを書くことよりはもちろんのこと、Rxを使うパターンよりわかりやすくなったと思います。

では、実際にアプリを作りながらどのような動きをするかみていきましょう。

== アプリを作ろう

=== 今回作るアプリ

作るのは「nasneに生えているHTTP APIを叩いてハードウェア情報と内蔵HDD情報を取得して表示する」アプリです。サンプルではminSdkVersion 21で作成します。

機器の自動検索はめんどくｓ…今回の目的では別になくてもいいのでやらずにnasneのIPアドレスを直打ちして使うようにします。またあくまでサンプルなので設計は超適当です。

@<comment>{TODO: nasne1台登録済みのアプリのMainActivityと登録フォームのスクショ}

=== 準備

Android Studioを起動し新しくプロジェクトを作ります(私はEmpty Activityを使用)。

忘れないうちにPermission(通信を行うので@<code>{<uses-permission android:name="android.permission.INTERNET" />})と依存ライブラリを追加します。

追加するのは

 * OkHttp3
 * Retrofit2
 * Coroutine

の3種類です。

App Moduleのbuild.gradleに以下のように追記します。バージョン指定は特に問題がなければその時点での最新バージョンでOKです。

//list[gradle][build.gradleに追加するライブラリ群][Gradle]{
implementation 'com.squareup.okhttp3:okhttp:3.9.1'
implementation 'com.squareup.okhttp3:logging-interceptor:3.9.1'
implementation 'com.squareup.retrofit2:retrofit:2.3.0'
implementation 'com.squareup.retrofit2:converter-gson:2.3.0'
implementation 'org.jetbrains.kotlinx:kotlinx-coroutines-core:0.21.1'
implementation 'org.jetbrains.kotlinx:kotlinx-coroutines-android:0.21.1'
implementation 'com.jakewharton.retrofit:retrofit2-kotlin-coroutines-experimental-adapter:1.0.0'
//}

@<list>{gradle}のうち@<code>{com.squareup}から始まっているものは定番なので特に説明は不要でしょう。

@<code>{kotlinx-coroutines-core}, @<code>{kotlinx-coroutines-android}はコルーチンを使うために必要なライブラリです。
kotlinにおける@<code>{async/await}は他の多くの言語と異なりキーワードでも標準ライブラリの一部でもありません。
@<code>{kotlinx-coroutines-core}はコルーチンそのものを使うためのライブラリ、@<code>{kotlinx-coroutines-android}はAndroidに依存した実装を含んでいます。

次の@<code>{retrofit2-kotlin-coroutines-experimental-adapter}はRetorofit2でコルーチンを扱うためのアダプターでJake神が開発し公開しています。
とても薄いライブラリなのでコルーチンをある程度学習したら一度読んでみるとよいでしょう。

あとは適当にサポートライブラリなど他に使いたいライブラリがあれば追加してsyncすれば準備完了です。
