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

　
