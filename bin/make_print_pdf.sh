#/bin/sh

# 印刷用

# コマンド確認
if type docker > /dev/null 2>&1; then
  docker run --rm -v `pwd`/src:/work vvakame/review /bin/sh -c "cd /work && review-pdfmaker config_print.yml"
  mv ./src/book.pdf ./
else
  echo "Docker がインストールされていません"
  exit 1
fi

