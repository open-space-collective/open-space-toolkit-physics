# Apache License 2.0

ARG JUPYTER_NOTEBOOK_IMAGE_REPOSITORY="jupyter/scipy-notebook:python-3.8.8"

FROM ${JUPYTER_NOTEBOOK_IMAGE_REPOSITORY}

LABEL maintainer="lucas@loftorbital.com"

ENV JUPYTER_ENABLE_LAB="yes"

# Set user to root

USER root

# Install Python utilities

RUN pip install --quiet "numpy" "pandas" "plotly" "ipywidgets>=7.6" "ipympl>=0.9.0"

# Install JupyterLab extensions

RUN jupyter labextension install --no-build \
        @jupyterlab/shortcuts-extension

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN chown -R ${NB_UID}:${NB_UID} /home/jovyan/.jupyter

# Install Open Space Toolkit

RUN pip install --quiet open-space-toolkit-physics

# Restore user

USER ${NB_UID}

# Disable token

CMD ["start-notebook.sh", "--NotebookApp.token=''"]
