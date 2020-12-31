---
layout: default
title: JapariMeter

header_top: true
header_title: JapariMeter
header_version: Rev.1
header_image: /assets/img/title/rev1.jpg
header_label: [supported]

subpages:
  - title: 頒布情報
    page: distribution
  - title: 更新履歴
    page: updates
---

## 特徴

JapariMeter は手のひらサイズで動く温湿度気圧計です。ボタン電池 1 つで気温、湿度、気圧がわかります。視認性の高い有機 EL ディスプレイ採用でどこでも見やすく。

## つかいかた

- 電源スイッチ：未使用時は電源をお切りください。
- ページ切り替えボタン：ボタンを押すと 気温 → 湿度 → 気圧 → 温湿度 → 不快指数 → 推定高度 →（気温）の順にページが切り替わります。
- 情報表示ボタン：公式サイトへのリンク、バージョン表記ページに切り替わります。

## こんなときは

- 電源が入らない、ディスプレイに何も表示されない、もしくは暗い：電池が消耗しています。新しい電池に交換してください。
- 「Error: Sensor connection」と表示される：製作者にご連絡ください。
- 計測値が「---」と表示される：電源を切り、10 秒ほどしてから再度電源を入れてください。表示が継続する場合は製作者にご連絡ください。

## 使用上の注意

- ディスプレイに有機 EL を使用しているため、長期間使用すると輝度に偏りが発生しますが異常ではありません。
- センサ部分に触れたり、息を吹きかけないでください。
- この温湿度気圧計はホビー用途です。厳密な測定を必要とする用途には使用できません。

## 安全な電池の取り扱い

- **電池のプラス極とマイナス極を逆にして挿入しないでください。**
- 長期間使用しないときは電池を抜いてください。
- 電池が消耗するとディスプレイが暗くなります。消耗した電池は速やかに交換してください。
- 使用後の電池は両面をセロハンテープで絶縁し、お近くの回収協力店などへ処分を依頼してください。

## 仕様

<table class="spec-table">
  <tbody>
    <tr>
      <th>製品名</th>
      <td>JapariMeter Rev.1</td>
    </tr>
    <tr>
      <th>製作期</th>
      <td>2021.01</td>
    </tr>
  </tbody>
</table>

<table class="spec-table">
  <tbody>
    <tr>
      <th>センサ</th>
      <td>BOSCH BME-280</td>
    </tr>
    <tr>
      <th>気温範囲</th>
      <td>-40〜80℃（精度: ±1.0℃）</td>
    </tr>
    <tr>
      <th>湿度範囲</th>
      <td>0〜100%（精度: ±3%）</td>
    </tr>
    <tr>
      <th>気圧範囲</th>
      <td>300〜1100hPa（精度: ±1.0hPa）</td>
    </tr>
    <tr>
      <th>計測間隔</th>
      <td>約 1 秒</td>
    </tr>
  </tbody>
</table>

<table class="spec-table">
  <tbody>
    <tr>
      <th>ディスプレイ</th>
      <td>128x32 ドット 0.91 インチ 有機 EL ディスプレイ</td>
    </tr>
  </tbody>
</table>

<table class="spec-table">
  <tbody>
    <tr>
      <th>電源</th>
      <td>CR2032 3V または DC 2.7-3.3V</td>
    </tr>
    <tr>
      <th>連続使用時間</th>
      <td>
        42 時間（推定）<br />
        <span class="foot-note">※消費電流を平均 5mA として容量 210mAh の電池を使った場合の計算値</span>
      </td>
    </tr>
  </tbody>
</table>

<table class="spec-table">
  <tbody>
    <tr>
      <th>大きさ（本体）</th>
      <td>約 43.0（幅） x12.6（高さ） x43.0（奥行） mm</td>
    </tr>
    <tr>
      <th>大きさ（ケース含む）</th>
      <td>約 50.0（幅） x19.6（高さ） x50.0（奥行） mm</td>
    </tr>
    <tr>
      <th>質量</th>
      <td>約 40 g（電池含む）</td>
    </tr>
  </tbody>
</table>

## ドキュメント

<table class="spec-table">
  <tbody>
    <tr>
      <th>組み立てマニュアル</th>
      <td></td>
    </tr>
    <tr>
      <th>回路図</th>
      <td></td>
    </tr>
  </tbody>
</table>

## ライセンス

**この作品は「けものフレンズ」の非公式ファン作品です。** 温湿度気圧計の使用により生じた損失については責任を負いかねます。

<table class="spec-table">
  <tbody>
    <tr>
      <th>
        <a href="https://fonts.google.com/specimen/Palanquin+Dark#about" target="_blank">Palanquin Dark</a><br />
        <span class="foot-note">by Pria Ravichandran</span>
      </th>
      <td>
        <span class="foot-note">Font for Logo and Text on board</span><br />
        These fonts are licensed under the <a href="https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL" target="_blank">Open Font License</a>.
      </td>
    </tr>
  </tbody>
</table>

<table class="spec-table">
  <tbody>
    <tr>
      <th>
        <a href="https://github.com/4ilo/ssd1306-stm32HAL" target="_blank">ssd1306-stm32HAL</a><br />
        <span class="foot-note">by 4ilo</span>
      </th>
      <td>
        <span class="foot-note">Display program and Font data</span><br />
        <a href="https://github.com/4ilo/ssd1306-stm32HAL/blob/master/LICENSE.md" target="_blank">MIT License</a>
      </td>
    </tr>
    <tr>
      <th>
        <a href="https://github.com/SuperHouse/esp-open-rtos" target="_blank">esp-open-rtos</a><br />
        <span class="foot-note">by SuperHouse Automation</span><br />
        <a href="https://github.com/ciastkolog/BMP280_STM32" target="_blank">BMP280_STM32</a><br />
        <span class="foot-note">by Ciastkolog</span>
      </th>
      <td>
        <span class="foot-note">Sensor program</span><br />
        <a href="https://github.com/SuperHouse/esp-open-rtos/blob/master/LICENSE" target="_blank">3-clause BSD License</a>
      </td>
    </tr>
  </tbody>
</table>

## 製作・制作

- 基板設計・実装・プログラム開発：七瀬 [@nanase_coder](https://twitter.com/nanase_coder)
- スペシャルサンクス：スティルマンさん [@lp_stillman](https://twitter.com/lp_stillman)

<p class="text-center margin-50 epitaph">Designed by Nanase, Fabricated in <span class="small-caps">JapariPark</span></p>
