# GMAT reference scripts

These [GMAT](https://software.nasa.gov/software/GSC-17177-1) scripts generate the reference data that the cross platform validation notebooks compare OSTk against:

- `scenario001-field-data-generation.script` → `gmat_physics/scenario001-field-data-generation.csv`

The notebooks read these CSV files from `data/gmat_physics/`, the parent of this directory.

## Where the report is written

Each script sets only a bare file name:

```
GMAT ReportFile1.Filename = 'scenario001-field-data-generation.csv';
```

GMAT writes a report file that has no directory in its name to `OUTPUT_PATH`, which is set in the GMAT startup file. The default is `<GMAT>/output/`. To regenerate the data in place, set `OUTPUT_PATH` to the `data/gmat_physics/` directory of your checkout:

1. Copy GMAT's default startup file and set `OUTPUT_PATH` to an absolute path, ending with a `/`. Keep the copy in GMAT's `bin` directory, because GMAT resolves relative paths in a startup file against the directory of the executable.
2. Run each script with `GmatConsole --startup_file <copy> --run <script>`.

From the root of this repository:

```shell
GMAT_BIN=/path/to/GMAT/bin  # contains GmatConsole and gmat_startup_file.txt
SCRIPTS_DIR="$PWD/tutorials/python/notebooks/Cross Platform Validation/data/gmat_physics/gmat_scripts"
OUTPUT_DIR="$(dirname "$SCRIPTS_DIR")/"  # data/gmat_physics/
STARTUP_FILE="$GMAT_BIN/gmat_startup_file.ostk.txt"

# LOG_FILE defaults to OUTPUT_PATH/GmatLog.txt; keep the log in GMAT's own output directory.
sed -e "s|^OUTPUT_PATH .*|OUTPUT_PATH = $OUTPUT_DIR|" \
    -e "s|^LOG_FILE .*|LOG_FILE = ROOT_PATH/output/GmatLog.txt|" \
    "$GMAT_BIN/gmat_startup_file.txt" > "$STARTUP_FILE"

"$GMAT_BIN/GmatConsole" --startup_file "$STARTUP_FILE" --run "$SCRIPTS_DIR/scenario001-field-data-generation.script"
```

To write the reports somewhere else, set `OUTPUT_DIR` to any absolute directory ending with `/`. The notebook (`OSTk Cross Platform Validation (Field Data Generation Scenario 1).ipynb`) reads only from `data/gmat_physics/`, so copy the CSV files there afterwards.
