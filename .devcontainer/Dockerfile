FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

RUN apt-get update && apt-get install -y git-lfs pip python3 clang-format cpanminus
RUN curl -o lcov-2.3.tar.gz -L https://github.com/linux-test-project/lcov/releases/download/v2.3/lcov-2.3.tar.gz
RUN tar -xvzf lcov-2.3.tar.gz
RUN cd lcov-2.3 && make install
RUN pip install clang-format --break-system-packages
RUN cpan -T App::cpanminus
RUN cpanm -n Cwd File::Spec::Functions Capture::Tiny DateTime DateTime::Format::ISO8601

