# Apache License 2.0

FROM python:3.6

LABEL maintainer="lucas@loftorbital.com"

RUN pip install pytest>=5.0.1

COPY bindings/python/requirements.txt /requirements.txt

RUN pip install -r /requirements.txt

ENV LD_LIBRARY_PATH="/usr/local/lib:/usr/local/lib/python3.6/site-packages:/open-space-toolkit/physics/lib"
ENV PYTHONPATH="/usr/local/lib/python3.6/site-packages:/open-space-toolkit/physics/lib"

COPY bindings/python/tools/python/OpenSpaceToolkit/Physics /usr/local/lib/python3.6/site-packages/OpenSpaceToolkit/Physics

RUN mkdir -p /open-space-toolkit \
 && mkdir -p /open-space-toolkit/physics

WORKDIR /open-space-toolkit/physics/test

CMD [ "pytest", "-sv" ]

################################################################################################################################################################
