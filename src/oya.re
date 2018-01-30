= iOSアプリ開発エンジニアがゼロからはじめるConstraintLayout入門

== 背景

2016年5月、Google I/O 2016で新しいViewGroupであるConstraintLayoutが発表されました。iOSのAutoLayoutと類似した概念を持ち、AndroidでもGUIで容易にレイアウトできるようになりました。
ちょうど1年前の2017年2月にConstraintLayout 1.0がリリースされ、現在では1.1.0-beta4までリリースされており、まもなく1.1.0のリリースがされようと差し迫っています。
そこで、iOSアプリ開発に従事していてAndroidに関する知見が少ない筆者が、iOSのAutoLayoutからみたConstraintLayoutの基本的なレイアウトの操作方法と、さらにConstraintLayout 1.1.0に加わる機能について触れていきます。

== 環境

* Macbook Pro(macOS Sierra)

* Xcode 9.2

* Android Stadio 3.0

* ConstraintLayout 1.1.0-beta4


== AutoLayoutのあれ、ConstraintLayoutでどうやるの？

=== 制約の追加

Xcodeでは、viewを選択後、画面右下のアイコン @<icon>{XcodeIconNewConstraints} をクリックして制約を追加します。(@<img>{XcodeNewConstraints})

//image[XcodeNewConstraints][Xcode,制約追加][scale=0.40]{
//}

一方AndroidStudioでは、viewを選択後、画面右側に @<b>{Attributes} 窓が自動で表示が切り替わります。
また、直接viewの四辺中央の白丸からドラッグすると緑色の矢印が表示され、制約を追加することができます。(@<img>{AndroidStudioNewConstraints})

//image[AndroidStudioNewConstraints][AndroidStudio,制約追加][scale=0.40]{
//}

アスペクト比率の追加変更は、選択したviewのlayout_widthまたはlayout_heightのいずれかがwrap_content以上の幅を持つ際に、Attributes窓左上に @<b>{三角} が表示されます。それをクリックすると右下に入力欄が表示され追加変更できるようになります。(@<img>{AndroidStudioNewConstraintsAspectRatio})

//image[AndroidStudioNewConstraintsAspectRatio][AndroidStudio,アスペクト比率追加][scale=0.40]{
//


=== 整列の追加

Xcodeでは、複数のviewを @<b>{⌘+クリック} で選択後、画面右下のアイコン @<icon>{XcodeIconNewAlignmentConstraints} をクリックして整列の制約を追加します。(@<img>{XcodeNewAlignmentConstraints})

//image[XcodeNewAlignmentConstraints][Xcode,整列追加窓][scale=0.40]{
//}

一方AndroidStudioでは、複数のviewを @<b>{Shift+クリック} で選択後、 画面上部に表示されたアイコン @<icon>{AndroidStudioIconNewAlignmentConstraints} (@<img>{AndroidStudioNewAlignmentConstraints}左)、または @<b>{右クリック} でサブメニュー (@<img>{AndroidStudioNewAlignmentConstraints}右) から整列の制約を追加します。 

//image[AndroidStudioNewAlignmentConstraints][AndroidStudio,左:アイコンから整列追加　右:サブメニューから整列追加]{
//}


== ConstraintLayoutでできること

=== Organize

TODO: 

=== Chain

TODO: 

=== Guildeline

TODO: 


== ConstraintLayoutでできないこと

=== priority

TODO:

=== viewgroup外のコンポーネントとの制約

TODO:

== まとめ

TODO: 
