# Apache License 2.0

ARG JUPYTER_NOTEBOOK_IMAGE_REPOSITORY=jupyter/scipy-notebook:x86_64-python-3.11.3

FROM ${JUPYTER_NOTEBOOK_IMAGE_REPOSITORY}

LABEL maintainer="lucas@loftorbital.com"

ENV JUPYTER_ENABLE_LAB yes

# Set user to root

USER root

# Install Python utilities

RUN apt-get update \
 && apt-get install -y curl \
 && rm -rf /var/lib/apt/lists/*

RUN pip install --quiet "numpy" "pandas" "plotly" "ipywidgets>=7.6" "ipympl>=0.9.0"

RUN jupyter labextension install --no-build \
        @jupyterlab/shortcuts-extension

COPY ./shortcuts-extension /home/jovyan/.jupyter/lab/user-settings/@jupyterlab/shortcuts-extension

RUN chown -R ${NB_UID}:${NB_GID} /home/jovyan

# Install Open Space Toolkit

RUN pip install open-space-toolkit-physics

# Install OSTk seed data
COPY --from=us.gcr.io/loft-orbital-public/software/open-space-toolkit/data:0.3.0 /open-space-toolkit/physics /usr/local/share/OpenSpaceToolkit/Physics

ENV OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY="/usr/local/share/OpenSpaceToolkit/Physics/coordinate/frame/providers/iers"
ENV OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY="/usr/local/share/OpenSpaceToolkit/Physics/environment/ephemerides/spice"
ENV OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY="/usr/local/share/OpenSpaceToolkit/Physics/environment/gravitational/earth"
ENV OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY="/usr/local/share/OpenSpaceToolkit/Physics/environment/magnetic/earth"
ENV OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY="/usr/local/share/OpenSpaceToolkit/Physics/environment/atmospheric/earth"

RUN chown -R ${NB_UID}:${NB_GID} /usr/local/share/OpenSpaceToolkit

# Restore user

USER ${NB_UID}

# Disable token

CMD ["start-notebook.sh", "--NotebookApp.token=''"]
