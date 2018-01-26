#/bin/sh

# 印刷用

# 表紙確認
if [ ! -f ./src/images/DroidKaigi_cover.pdf ]; then
  echo "src/images に表紙がありません"
  exit 1
fi

# 裏表紙確認
if [ ! -f ./src/images/DroidKaigi_backcover.pdf ]; then
  echo "src/images に裏表紙がありません"
  exit 1
fi

# コマンド確認
if type "docker gs" > /dev/null 2>&1; then
  docker run --rm -v `pwd`/src:/work vvakame/review /bin/sh -c "cd /work && review-pdfmaker config_print.yml"
  gs -q -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=book.pdf ./src/images/DroidKaigi_cover.pdf ./src/book.pdf ./src/images/DroidKaigi_backcover.pdf
  rm ./src/book.pdf
else
  echo "Docker または Ghostscript がインストールされていません"
  exit 1
fi

