= iOSアプリ開発エンジニアがゼロからはじめるConstraintLayout入門

== 背景

2016年5月、Google I/O 2016で新しいViewGroupであるConstraintLayout@<fn>{DocsConstraintLayout}が発表されました。iOSのAutoLayoutと類似した概念を持ち、AndroidでもGUIで容易にレイアウトできるようになりました。
ちょうど1年前の2017年2月にConstraintLayout 1.0がリリースされ、現在では1.1.0-beta4までリリースされており、まもなく1.1のリリースがされようと差し迫っています。
そこで、iOSアプリ開発に従事していてAndroidに関する知見が少ない筆者が、iOSのAutoLayoutの知見を駆使して、ConstraintLayoutを使ったGUI上の基本的なレイアウトの操作方法と、ConstraintLayout 1.1で加わる新機能について触れていきます。
//footnote[DocsConstraintLayout][@<href>{https://developer.android.com/reference/android/support/constraint/ConstraintLayout.html}]

== 環境

* Macbook Pro(macOS Sierra)

* Xcode 9.2

* Android Stadio 3.1 Preview 9

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


=== 等幅・等高の追加

TODO: Chainの説明

//footnote[DocsChain][@<href>{https://developer.android.com/reference/android/support/constraint/ConstraintLayout.html#Chains}]


=== Priority

AutoLayoutでは、制約毎にPriorityを 1~1000 の数値で指定して適用する制約に優先度を付与することができますが、ConstraintLayoutでは同種の制約を複数付与することができず、制約自体にPriorityの概念がありません。
しかし、ConstraintLayout 1.1で Barriar@<fn>{DocsBarriar} が追加されました。
Barrierは、指定した複数のviewの一方向に対して最大幅にガイドラインを維持してくれるものです。
@<img>{AndroidStudioBarrier} は緑のviewとのviewの右側にBarrierを追加した例ですが、右側の赤のviewは緑と青の最大幅に合わせてレイアウトできます。

//image[AndroidStudioBarrier][AndroidStudio,Barrierサンプル]{
//}

//footnote[DocsBarriar][@<href>{https://developer.android.com/reference/android/support/constraint/Barrier.html}]


== ConstraintLayoutでできること

=== Circular Positioning(1.1~)

対象のviewを起点する円周上にレイアウトできる機能です。Attributes の Constraints に、@<i>{circle}, @<i>{circleAngle}, @<i>{circleRadius} の3つの項目を指定します。
@<i>{circle} には中心にするviewのid、@<i>{circleAngle} には回転させる角度(degree)、@<i>{circleRadius} には中心からの距離(dp) をそれぞれ指定します。
角度については、中心から上方向が角度の開始軸となり、時計回りに配置されます。(@<img>{AndroidStudioCircularPositioning})

※執筆時点で、GUI上で制約を追加できませんでした。

//image[AndroidStudioCircularPositioning][AndroidStudio,Circular Positioning][scale=0.40]{
//}


== ConstraintLayoutでできないこと

=== 階層が異なるViewとの制約

突然ですが、@<img>{XcodeSamplePopup}右 のようなレイアウトを組むとき、ポップアップの枠からはみ出してるポップアップ右上の閉じるボタンにどのような制約をかけるべきか悩んだことありませんか？
筆者の場合、@<img>{XcodeSamplePopup}左 のように、閉じるボタンを画面中央に配置したポップアップと同じ階層に配置し、ポップアップの右上に整列後はみ出す分のネガティブ値を指定します。

//image[XcodeSamplePopup][Xcode,ポップアップ][scale=0.40]{
//}

ここで、この閉じるボタンの配置階層を一つ上にあげようとした場合、AutoLayoutではポップアップと上記と同じように制約を追加することが可能でます。
しかし、ConstraintLayoutでは親と同階層のViewにのみ制約を付与が許されていないため、階層を意識したLayoutをする必要があります。


== まとめ

ConstraintLayoutを使って、Androidの基本的なレイアウトの操作方法を理解することができました。
コードに触れることなくGUIのみで操作できることで、デザイナーなどの非エンジニアでも作業することへの敷居がだいぶ低くなったのではないでしょうか？。
また、ConstraintLayoutには本章で触れなかった機能があります。まだConstraintLayoutに触れていない方は、ぜひお手元のAndroidStudioで試してみてください。
