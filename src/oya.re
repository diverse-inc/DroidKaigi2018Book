= iOSアプリ開発エンジニアがゼロからはじめるConstraintLayout入門

== 背景

Swift3.0がで始めた2016年から1年半、筆者はiOSアプリ開発に従事していました。InterfaceBuilderでのGUIレイアウトも慣れてきて、アプリのデザイン変更にもすばやく対応できるようになったと思い込んでいます。
そんなある日、上司から呼び出され、「◯◯さん、来月からAndroid開発よろしくお願いします。」と、突然Androidアプリ開発できる好機を得ました。
そこで筆者がAndroid入門するにあたって、iOSのAutoLayoutの知識を活用してUIを構成できるConstraintLayoutに焦点をあて、GUIレイアウトの基本的な機能の比較を図解してまとめてみました。


== 環境

* Macbook Pro(macOS Sierra)

* Xcode 9.2

* Android Stadio 3.0


== AutoLayoutのあれ、ConstraintLayoutでどうやるの？

=== 制約の追加

Xcodeでは、viewを選択後、画面右下のアイコン @<icon>{XcodeIconNewConstraints} をクリックして制約を追加します。(@<img>{XcodeNewConstraints})

//image[XcodeNewConstraints][Xcode,制約追加][scale=0.40]{
//}

一方AndroidStudioでは、viewを選択後、画面右側に @<b>{Attributes} 窓が自動で表示が切り替わります。
また、直接viewの四辺中央の白丸からドラッグすると緑色の矢印が表示され、制約を追加することができます。(@<img>{AndroidStudioNewConstraints})

//image[AndroidStudioNewConstraints][AndroidStudio,制約追加][scale=0.40]{
//}

アスペクト比率の追加変更は、選択したviewのlayout_widthまたはlayout_heightのいずれかがmatch_parentに指定した際に、@<b>{Attributes} 窓左上に三角が表示されます。それをクリックすると右下に入力欄が表示され追加変更できるようになります。(@<img>{AndroidStudioNewConstraintsAspectRatio})

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
