# structure variables
BUILD_DIR="build/"
EXE_NAME="SentimentAnalyzer"

# input data files
DATA_DIR="../data/"
TRAIN_DATA=${DATA_DIR}"dev-train-data-sm.csv"
TRAIN_TARGET=${DATA_DIR}"dev-train-target-sm.csv"
TEST_DATA=${DATA_DIR}"dev-test-data.csv"
TEST_TARGET=${DATA_DIR}"dev-test-target.csv"

# executable variables
BUILD_SUCCESS=0
RUN_TESTS=0

# print script usage
function usage () {
    echo "Usage:"
    echo "-h                       print usage"
    echo "-t                       run unit tests"
    echo "-b                       print brief output to console"
    echo "-f OUTPUT_FILENAME       print extensive output to data file (provide a file name)"
    echo "-p INPUT_FILEPATH        supply input file with graph data (provide input file's path)"
}

function exit_error () {
    usage
    exit 1
}

# process flags if there are any
# default behavior will execute sentiment analysis on files in 'data' directory
while getopts "ht" options; do
    case "${options}" in
        h)
            usage
            ;;
        t)
            RUN_TESTS=1
            ;;
        :)
            echo "Error: '-${OPTARG}' requires an argument."
            exit_error
            ;;
        *)
            echo "Error: Unrecognized flag."
            exit_error
            ;;
    esac
done

#---------- build ----------#
cd ${BUILD_DIR}
cmake .
make && BUILD_SUCCESS=1

#----------- run -----------#
if [ ${BUILD_SUCCESS} -eq 1 ]
then
    if [ ${RUN_TESTS} -eq 1 ]
    then
        # no CL args = run catch tests
        ./${EXE_NAME}
    else
        ./${EXE_NAME} ${TRAIN_DATA} ${TRAIN_TARGET} ${TEST_DATA} ${TEST_TARGET}
    fi
fi