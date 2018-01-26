#/bin/sh
docker run --rm -v `pwd`/src:/work vvakame/review /bin/sh -c "cd /work && review-pdfmaker config.yml"
mv ./src/book.pdf ./
