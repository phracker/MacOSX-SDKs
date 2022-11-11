SOURCE=$1
PRODUCTS=$2
SDK_NAME=$3
#SDK_NAME=macosx.internal
SDKROOT=$(xcrun --sdk ${SDK_NAME} --show-sdk-path)
IIG=$(xcrun -sdk ${SDK_NAME} -find iig)

FRAMEWORK_NAME=$(basename ${SOURCE})

if [[ ${DRIVERKIT} == 1 ]]; then
	DRIVERKITRUNTIMEROOT=${DRIVERKITROOT}/Runtime
	SDKHEADERSROOT=${DRIVERKITRUNTIMEROOT}
	DRIVERKITSDKHEADERSROOT=${DRIVERKITROOT}
fi

CFLAGS_sdk_include="-isysroot ${SDKROOT} -isystem ${SDKROOT}/${SDKHEADERSROOT}/System/Library/Frameworks/System.framework/PrivateHeaders -iframework ${SDKROOT}/${SDKHEADERSROOT}/System/Library/Frameworks -isystem ${SDKROOT}/${SDKHEADERSROOT}/usr/local/include -isystem ${SDKROOT}/${SDKHEADERSROOT}/usr/include"

OTHER_IIG_FLAGS=${OTHER_IIG_FLAGS:-}
OTHER_IIG_CFLAGS=${OTHER_IIG_CFLAGS:-${CFLAGS_sdk_include}}" -x c++ -std=gnu++1z -fno-exceptions -D__IIG=1 -DPLATFORM_DriverKit=1 ${DEPLOYMENT_TARGET_DEFINES}"

FRAMEWORK=${PRODUCTS}/${FRAMEWORK_NAME}

rm -rf ${FRAMEWORK}
ditto ${SOURCE} ${FRAMEWORK}

shopt -s nullglob
FILES="${FRAMEWORK}/Headers/*.iig ${FRAMEWORK}/PrivateHeaders/*.iig"

for DEF in ${FILES}; do
	${IIG} --def ${DEF} --header ${DEF%.iig}.h --impl /dev/null ${OTHER_IIG_FLAGS} -- ${OTHER_IIG_CFLAGS};
done

