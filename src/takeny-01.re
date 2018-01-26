= OkHttp3+Retrofit2+Kotlin Coroutineでつくるnasneクライアント最初の一歩
//lead{
AndroidでHTTPによるAPI通信を行うときに使うライブラリは OkHttp3, Retrofit2そしてRxJavaの組み合わせが定番です。

しかしKotlin1.1からExperimentalではありますがCoroutineが搭載されました。Coroutineを使うことによってこれまでのコールバック地獄やRxのメソッドチェーンから解放され
直感的なコードで表現できるようになることでしょう。

またCoroutineはKotlin1.2でProduct Readyであることが宣言され、1.3ではいよいよExperimentalが外れる予定でとりあえず簡単な使い方を知って勉強し始めるにはちょうどいいタイミングかもしれません。

そこで本章ではコルーチンの簡単な説明とnasneのAPIを叩いてハードウェア情報や内蔵HDDの情報を取得するクライアントアプリをOkHttp3+Retrofit2+Coroutineを使って作ってみた話を書きます。
//}

//footnote[nasne-r][本文中に出てくる"PS4", "nasne(ナスネ)"および"torne(トルネ)"は株式会社ソニー・インタラクティブエンタテインメントの登録商標または商標です。]

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

=== 準備

Android Studioを起動し新しくプロジェクトを作ります(私はEmpty Activityを使用)。

通信を行うので@<code>{<uses-permission android:name="android.permission.INTERNET" />}と依存ライブラリを追加します。

追加するライブラリは

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

@<list>{gradle}のうちokhttpとretrofitは定番なので説明を省きます。

@<code>{kotlinx-coroutines-core}, @<code>{kotlinx-coroutines-android}はコルーチンを使うために必要なライブラリです。
kotlinにおける@<code>{async/await}は他の多くの言語と異なりキーワードでも標準ライブラリの一部でもありません。
@<code>{kotlinx-coroutines-core}はコルーチンそのものを使うためのライブラリ、@<code>{kotlinx-coroutines-android}はAndroidに依存した実装を含んでいます。

次の@<code>{retrofit2-kotlin-coroutines-experimental-adapter}はRetorofit2でコルーチンを扱うためのアダプターでJake神が開発し公開しています。
とても薄いライブラリなのでコルーチンをある程度学習したら一度読んでみるとよいでしょう。

あとは適当にサポートライブラリなど他に使いたいライブラリがあれば追加してsyncすれば準備完了です。

=== 通信部分を作る

では、早速実装をすすめていきましょう。まずはnasneのAPIの仕様を知る必要がありますが、残念ながら一般には公開されていません。
nasneはPS4やアプリのクライアントを使って確認する他にnasneのIPアドレスをブラウザに入力してアクセスする方法があります。

ブラウザで@<code>{http://<nasneのIPアドレス>/}にアクセスすると@<code>{http://<nasneのIPアドレス>:64210/nasne_home/index.html}にリダイレクトされます。
メニューを眺めていくと型番やHDDの情報を見ることができます。つまりブラウザとnasneは何らかのAPIを通じて通信していることになります。
調べ方やエンドポイントをここに具体的に書くと各方面から怒られるかもしれないので書けないですがHTMLやJavaScriptをずっと読んでいくとそれっぽいものを発見できると思います。

さて、エンドポイントがわかったら実際叩いてみましょう。ハードウェア情報とHDD情報を取得するAPIは特に認証は不要なのでcurlで叩くことができます。
すると以下のようなレスポンスが得られると思います。(@<list>{nasne-hardware-info-response}, @<list>{nasne-hdd-info-response})

//list[nasne-hardware-info-response][ハードウェア情報APIのレスポンス][JSON]{
{
  "errorcode": 0,
  "hardwareVersion": 1,
  "productName": "CECH-ZNR1J"
}
//}

//list[nasne-hdd-info-response][HDD情報APIのレスポンス][JSON]{
{
  "HDD": {
    "totalVolumeSize": 998373937152,
    "freeVolumeSize": 330503405568,
    "usedVolumeSize": 667870531584,
    "serialNumber": "JA1000101XXXXX",
    "id": 0,
    "internalFlag": 0,
    "mountStatus": 1,
    "registerFlag": 1,
    "format": "xfs",
    "name": "hdd0",
    "vendorID": "ATA",
    "productID": "HGST HTS541010A9"
  },
  "errorcode": 0
}
//}

これをJsonからオブジェクトに変換するためのクラスを定義します。Kotlinには@<code>{data class}があるのですっきり定義することができます。
なお、HDD情報については使わない項目もあるので今回必要なもののみ定義しています。

//list[nasne-hardware-info-class][ハードウェア情報クラス][kt]{
data class Hardware(val hardwareVersion: Int, val productName: String)
//}

//list[nasne-hdd-info-class][HDD情報クラス][kt]{
data class NasneHddInfo(@SerializedName("HDD") val hdd: Hdd, val errorCode: Int)
data class Hdd(val totalVolumeSize: Long,
    val freeVolumeSize: Long,
    val usedVolumeSize: Long,
    val format: String)
//}

次にHttpクライアントを実装していきます。
まずはRetorofitのInterface(@<list>{nasne-api-interface})です。基本的にはRxJavaを使った場合と変わりませんが戻り値の型は@<code>{Deferred<T>}を指定します。
@<code>{Deferred<T>}をawaitすると値が返ってくるまでコルーチンが中断されます。

(エンドポイントはここに書くことは控えさせていただきます。@<code>{<<CENCERED>>}を適当なエンドポイントに書き換えてください)

//list[nasne-api-interface][Retorfit用のinterface][kt]{
interface NasneApi {
    @GET("<<CENCERED>>")
    fun getHardwareVersion(): Deferred<NasneHardwareInfo>

    @GET("<<CENCERED>>")
    fun getInternalHddInfo(): Deferred<NasneHddInfo>
}
//}

次にHttpクライアントやRetrofitのインスタンスを作るクラスを用意します(@<list>{client-module})。

//list[client-module][ネットワーククライアントクラス][kt]{
class NasneApiClientModule {
    fun provideHttpClientForNasneApi(isDebug: Boolean): OkHttpClient =
        OkHttpClient.Builder()
            .addInterceptor(HttpLoggingInterceptor().apply {
                level = if (isDebug) {
                    HttpLoggingInterceptor.Level.BODY
                } else {
                    HttpLoggingInterceptor.Level.NONE
                }
            })
            .build()

    fun provideRetrofitForNasneApi(httpClient: OkHttpClient, baseURL: String): Retrofit =
        Retrofit.Builder()
            .client(httpClient).baseUrl(baseURL)
            .addConverterFactory(GsonConverterFactory.create())
            .addCallAdapterFactory(CoroutineCallAdapterFactory())
            .build()

    fun provideNasneApi(retrofit: Retrofit): NasneApi =
        retrofit.create(NasneApi::class.java)
}
//}

OkHttpClientオブジェクトとInterfaceからAPIクライアントを作るところは今まで通りです。Retotorfitオブジェクトを作るときに指定する
CallAdapterに@<code>{CoroutineCallAdapterFactory}を指定します。すると@<code>{Call<T>}が@<code>{Deferred<T>}に変換されます。

これでクライアントの準備はできました。いよいよこれらを使って実際に画面上に出してみましょう。

=== 結果を表示する

とりあえず適当にレイアウトを組みました。(Design Support Libraryを使用しています。)

//image[screenshot01][レイアウト][scale=0.3]{
//}

IPアドレスを入力し取得ボタンをタップすると型番、世代、ファイルシステム、合計容量、使用容量、空き容量が表示される簡単なアプリです。

//pagebreak

//list[main-activity-click][取得ボタンをタップしたときのListenerの実装][kt]{
  nasneGetInfoButton.setOnClickListener {
      val baseUrl = "http://%s:64210".format(nasneIpAddressEditText.tex
      val retrofit = networkModule
          .provideRetrofitForNasneApi(httpClient, baseUrl)
      val api = networkModule.provideNasneApi(retrofit)
      launch(UI) {
          try {
              val hardwareInfo = api.getHardwareVersion().await()
              val hddInfo = api.getInternalHddInfo().await().hdd
              nasneModelName.text = hardwareInfo.productName
　　　　　　    nasneModelVersion.text = hardwareInfo.hardwareVersion.toString()
              nasneFileSystem.text = hddInfo.format
              nasneStorageTotalVolume.text = hddInfo.totalVolumeSize.toString()
              nasneStorageFreeVolume.text = hddInfo.freeVolumeSize.toString()
              nasneStorageUsageVolume.text = hddInfo.usedVolumeSize.toString()
          } catch (e: HttpException) {
              when(e.code()) {
                  404 -> {
                      Toast.makeText(this@MainActivity, "nasne Not Found", Toast.LENGTH_LONG).show()
                  }
                  else -> {
                      Toast.makeText(this@MainActivity, "ERROR!", Toast.LENGTH_LONG).show()
                  }
              }
      　　}
  　　}
  }
//}

@<list>{main-activity-click}は取得ボタンをタップした時のclickListenerを抜粋したものです。軽く眺めるだけでコールバックやRxを使った場合とは全く違うことがわかります。
