#/bin/sh

# Web配布用

docker run --rm -v `pwd`/src:/work vvakame/review /bin/sh -c "cd /work && review-pdfmaker config.yml"
mv ./src/book.pdf ./
