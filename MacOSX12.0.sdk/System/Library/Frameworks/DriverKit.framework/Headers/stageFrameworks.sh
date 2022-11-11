inputIdx=0
while [[ $inputIdx -lt ${SCRIPT_INPUT_FILE_COUNT} ]]; do
	tmp="SCRIPT_INPUT_FILE_$inputIdx"
	FRAMEWORK=${!tmp}
	if [[ -f ${FRAMEWORK}/Headers/stageFramework.sh ]]; then
		. ${FRAMEWORK}/Headers/stageFramework.sh ${FRAMEWORK} ${BUILT_PRODUCTS_DIR} ${SDK_NAME}
	else
		. ${SDKROOT}/System/Library/Frameworks/DriverKit.framework/Headers/stageFramework.sh ${FRAMEWORK} ${BUILT_PRODUCTS_DIR} ${SDK_NAME}
	fi
	let inputIdx=inputIdx+1
done
