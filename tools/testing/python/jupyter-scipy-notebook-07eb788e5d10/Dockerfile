/// Apache License 2.0 

FROM jupyter/scipy-notebook:07eb788e5d10

LABEL maintainer="lucas@loftorbital.com"

RUN pip install pytest>=5.0.1

COPY bindings/python/requirements.txt /requirements.txt

RUN pip install -r /requirements.txt

ENV LD_LIBRARY_PATH="/usr/local/lib:/opt/conda/lib/python3.6/site-packages:/home/jovyan/open-space-toolkit/physics/lib"
ENV PYTHONPATH="/opt/conda/lib/python3.6/site-packages:/home/jovyan/open-space-toolkit/physics/lib"

COPY bindings/python/tools/python/OpenSpaceToolkit/Physics /opt/conda/lib/python3.6/site-packages/OpenSpaceToolkit/Physics

RUN mkdir -p /home/jovyan/open-space-toolkit \
 && mkdir -p /home/jovyan/open-space-toolkit/physics

WORKDIR /home/jovyan/open-space-toolkit/physics/test

CMD [ "pytest", "-sv" ]

################################################################################################################################################################
