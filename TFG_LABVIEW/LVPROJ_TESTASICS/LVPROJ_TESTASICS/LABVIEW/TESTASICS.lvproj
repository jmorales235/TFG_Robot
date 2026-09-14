<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="19008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">false</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Project Documentation" Type="Folder">
			<Item Name="Documentation Images" Type="Folder">
				<Item Name="loc_open_data_typedef.png" Type="Document" URL="../documentation/loc_open_data_typedef.png"/>
				<Item Name="loc_open_states_typedef.png" Type="Document" URL="../documentation/loc_open_states_typedef.png"/>
				<Item Name="loc_simple_state_machine.png" Type="Document" URL="../documentation/loc_simple_state_machine.png"/>
				<Item Name="loc_state_transition.png" Type="Document" URL="../documentation/loc_state_transition.png"/>
				<Item Name="loc_transition_error.png" Type="Document" URL="../documentation/loc_transition_error.png"/>
				<Item Name="loc_use_state_data.png" Type="Document" URL="../documentation/loc_use_state_data.png"/>
				<Item Name="loc_conditional_state_transition.png" Type="Document" URL="../documentation/loc_conditional_state_transition.png"/>
				<Item Name="loc_new_button.png" Type="Document" URL="../documentation/loc_new_button.png"/>
				<Item Name="loc_new_button_transition.png" Type="Document" URL="../documentation/loc_new_button_transition.png"/>
				<Item Name="loc_new_button_value_change.png" Type="Document" URL="../documentation/loc_new_button_value_change.png"/>
				<Item Name="loc_new_state.png" Type="Document" URL="../documentation/loc_new_state.png"/>
			</Item>
			<Item Name="Simple State Machine Documentation.html" Type="Document" URL="../documentation/Simple State Machine Documentation.html"/>
		</Item>
		<Item Name="VI&apos;s" Type="Folder" URL="../VI&apos;s">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Type_defs" Type="Folder" URL="../Type_defs">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="MAIN_STANDALONE.vi" Type="VI" URL="../MAIN_STANDALONE.vi"/>
		<Item Name="MAIN_CALLED_TESTASICS.vi" Type="VI" URL="../MAIN_CALLED_TESTASICS.vi"/>
		<Item Name="SHARED VI&apos;S.lvlib" Type="Library" URL="../../../SHARED VI&apos;S/SHARED VI&apos;S.lvlib"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="subTimeDelay.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/TimeDelayBlock.llb/subTimeDelay.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="FindElementStartByName.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindElementStartByName.vi"/>
				<Item Name="FindCloseTagByName.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindCloseTagByName.vi"/>
				<Item Name="FindMatchingCloseTag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindMatchingCloseTag.vi"/>
				<Item Name="FindElement.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindElement.vi"/>
				<Item Name="FindEmptyElement.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindEmptyElement.vi"/>
				<Item Name="FindFirstTag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindFirstTag.vi"/>
				<Item Name="ParseXMLFragments.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/ParseXMLFragments.vi"/>
				<Item Name="compatCalcOffset.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatCalcOffset.vi"/>
				<Item Name="compatOpenFileOperation.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatOpenFileOperation.vi"/>
				<Item Name="compatFileDialog.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatFileDialog.vi"/>
				<Item Name="Open_Create_Replace File.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/Open_Create_Replace File.vi"/>
				<Item Name="Read From XML File(string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File(string).vi"/>
				<Item Name="Read From XML File(array).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File(array).vi"/>
				<Item Name="Read From XML File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File.vi"/>
				<Item Name="1D String Array to Delimited String.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/1D String Array to Delimited String.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="VISA Find Search Mode.ctl" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Find Search Mode.ctl"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="QR Code Search Options.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/QR Code Search Options.ctl"/>
				<Item Name="Demodulation Mode.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/Demodulation Mode.ctl"/>
				<Item Name="Cell Sample Size.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/Cell Sample Size.ctl"/>
				<Item Name="Cell Filter Mode.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/Cell Filter Mode.ctl"/>
				<Item Name="QR Code Description Options.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/QR Code Description Options.ctl"/>
				<Item Name="Data Matrix Polarity.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/Data Matrix Polarity.ctl"/>
				<Item Name="QR Code Model Type.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/QR Code Model Type.ctl"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="IMAQ Create" Type="VI" URL="/&lt;vilib&gt;/vision/Basics.llb/IMAQ Create"/>
				<Item Name="IMAQ Image.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Image Controls.llb/IMAQ Image.ctl"/>
				<Item Name="Image Type" Type="VI" URL="/&lt;vilib&gt;/vision/Image Controls.llb/Image Type"/>
				<Item Name="IMAQ ReadFile" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ ReadFile"/>
				<Item Name="NI_Vision_Development_Module.lvlib" Type="Library" URL="/&lt;vilib&gt;/vision/NI_Vision_Development_Module.lvlib"/>
				<Item Name="ROI Descriptor" Type="VI" URL="/&lt;vilib&gt;/vision/Image Controls.llb/ROI Descriptor"/>
				<Item Name="QR Code Stream Mode Type.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/QR Code Stream Mode Type.ctl"/>
				<Item Name="QR Code Report.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Instrument.llb/QR Code Report.ctl"/>
				<Item Name="IMAQ Dispose" Type="VI" URL="/&lt;vilib&gt;/vision/Basics.llb/IMAQ Dispose"/>
				<Item Name="Find First Error.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find First Error.vi"/>
				<Item Name="Close File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Close File+.vi"/>
				<Item Name="compatReadText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatReadText.vi"/>
				<Item Name="Read File+ (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read File+ (string).vi"/>
				<Item Name="Open File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Open File+.vi"/>
				<Item Name="Read Characters From File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Characters From File.vi"/>
				<Item Name="System Directory Type.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/sysdir.llb/System Directory Type.ctl"/>
				<Item Name="Get System Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/sysdir.llb/Get System Directory.vi"/>
				<Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="8.6CompatibleGlobalVar.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/config.llb/8.6CompatibleGlobalVar.vi"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="subDisplayMessage.vi" Type="VI" URL="/&lt;vilib&gt;/express/express output/DisplayMessageBlock.llb/subDisplayMessage.vi"/>
			</Item>
			<Item Name="instr.lib" Type="Folder">
				<Item Name="VI Tree.vi" Type="VI" URL="/&lt;instrlib&gt;/Agilent 81150/Public/VI Tree.vi"/>
			</Item>
			<Item Name="Coordenadas_estacion.ctl" Type="VI" URL="../../../LVPROJ_CONFIG_ESTACION/Type_defs/Coordenadas_estacion.ctl"/>
			<Item Name="Data_Bandeja.ctl" Type="VI" URL="../../../LVPROJ_CREAR BANDEJAS/Type_defs/Data_Bandeja.ctl"/>
			<Item Name="Configuracion_estación.ctl" Type="VI" URL="../../../LVPROJ_CONFIG_ESTACION/Type_defs/Configuracion_estación.ctl"/>
			<Item Name="Comandos.ctl" Type="VI" URL="../../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Comandos.ctl"/>
			<Item Name="Enviar_comando.vi" Type="VI" URL="../../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/Enviar_comando.vi"/>
			<Item Name="Estados_arduino.ctl" Type="VI" URL="../../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Estados_arduino.ctl"/>
			<Item Name="SHARED TYPES.lvlib" Type="Library" URL="../../../SHARED TYPES/SHARED TYPES.lvlib"/>
			<Item Name="Ack_comando_arduino.vi" Type="VI" URL="../../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/Ack_comando_arduino.vi"/>
			<Item Name="wait_&amp;ackChar.vi" Type="VI" URL="../../../LVPROJ_LEER_QR/LABVIEW/VI&apos;S/wait_&amp;ackChar.vi"/>
			<Item Name="CapturaImagenyQR_subVI_pruebas.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Origen Socket SERVO_PCB_BUENO_v5 (muchos asics)/CapturaImagenyQR_subVI_pruebas.vi"/>
			<Item Name="nivissvc.dll" Type="Document" URL="nivissvc.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="nivision.dll" Type="Document" URL="nivision.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="QR_error_generator.vi" Type="VI" URL="../../../LVPROJ_LEER_QR/LABVIEW/VI&apos;S/QR_error_generator.vi"/>
			<Item Name="Agilent 81150.lvlib" Type="Library" URL="../../../../../Test Asic Javi_2021/Viejos/Alfredo LABVIEW/Set-up verificador ASICs/Lib Agilent 81160A/Agilent 81150/Agilent 81150.lvlib"/>
			<Item Name="Tektronix DPO MSO 2000 4000 Series.lvlib" Type="Library" URL="../../../../../Test Asic Javi_2021/Tektronix DPO MSO 2000 4000 Series/Tektronix DPO MSO 2000 4000 Series.lvlib"/>
			<Item Name="DP832_Close.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Rigol DP832/DP832_Close.vi"/>
			<Item Name="DP832_Write.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Rigol DP832/DP832_Write.vi"/>
			<Item Name="DP832_Local Mode.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Rigol DP832/DP832_Local Mode.vi"/>
			<Item Name="FTDI_Status_Explanation.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/D2XX_FT2232HL/FTDI_Status_Explanation.vi"/>
			<Item Name="FT_status to error.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/FT_status to error.vi"/>
			<Item Name="FT_Close_Device.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/D2XX_FT2232HL/FT_Close_Device.vi"/>
			<Item Name="CRC32.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/CRC32.vi"/>
			<Item Name="global erroes cluster.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/global erroes cluster.ctl"/>
			<Item Name="Global cuenta erroes.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Global cuenta erroes.vi"/>
			<Item Name="REPORT.Create Table.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Create Table.vi"/>
			<Item Name="REPEORT.CAMBIO LINEA.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPEORT.CAMBIO LINEA.vi"/>
			<Item Name="REPORT.Create line.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Create line.vi"/>
			<Item Name="FT_Get_Library_Version.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/D2XX_FT2232HL/FT_Get_Library_Version.vi"/>
			<Item Name="FT_Get_Driver_Version.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/D2XX_FT2232HL/FT_Get_Driver_Version.vi"/>
			<Item Name="GenPulse_configurar.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/GenPulse_configurar.ctl"/>
			<Item Name="TEST.TEST INFO PC.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST INFO PC.ctl"/>
			<Item Name="TEST.TEST TEST INFO.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST TEST INFO.ctl"/>
			<Item Name="TEST.TEST CONFIG VGA.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST CONFIG VGA.ctl"/>
			<Item Name="TEST.TEST EXECUTION TEST.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST EXECUTION TEST.ctl"/>
			<Item Name="test_result fvasic.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/test_result fvasic.ctl"/>
			<Item Name="TEST.TEST RESULT.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST RESULT.ctl"/>
			<Item Name="TEST.TEST CONFIG TEST.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST CONFIG TEST.ctl"/>
			<Item Name="TEST.TEST CONFIG TEST MATRIZ.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST CONFIG TEST MATRIZ.ctl"/>
			<Item Name="DP832_Control Channels.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Rigol DP832/DP832_Control Channels.ctl"/>
			<Item Name="TEST.TEST CONFIG HW.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEST CONFIG HW.ctl"/>
			<Item Name="Test.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test.ctl"/>
			<Item Name="UTIL.Get info pc.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/UTIL.Get info pc.vi"/>
			<Item Name="REPORT.Main others.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Main others.vi"/>
			<Item Name="REPORT.BIN TO STRING.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.BIN TO STRING.vi"/>
			<Item Name="REPORT.DIGIAL offset.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.DIGIAL offset.vi"/>
			<Item Name="REPORT.Analog offset adders_.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Analog offset adders_.vi"/>
			<Item Name="REPORT.Analog offset_.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Analog offset_.vi"/>
			<Item Name="cruce por cero adders.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/cruce por cero adders.vi"/>
			<Item Name="REPORT.Rate scan ADD.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Rate scan ADD.vi"/>
			<Item Name="Rate Scan. Ajuste por minimos cuadrados.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Rate Scan. Ajuste por minimos cuadrados.vi"/>
			<Item Name="REPORT.Rate scan.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Rate scan.vi"/>
			<Item Name="REPORT.Max Min P N.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Max Min P N.vi"/>
			<Item Name="REPORT.DESVIATION DAC TEST.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.DESVIATION DAC TEST.vi"/>
			<Item Name="REPORT.Register Test.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Register Test.vi"/>
			<Item Name="REPORT.Voltage asic.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.Voltage asic.vi"/>
			<Item Name="REPORT.BIN TO STRING ACTIVE TEST.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.BIN TO STRING ACTIVE TEST.vi"/>
			<Item Name="report.bin to bin result test.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/report.bin to bin result test.vi"/>
			<Item Name="REPORT.init test.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/REPORT.init test.vi"/>
			<Item Name="clipboard.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/clipboard.vi"/>
			<Item Name="FT_Error_codes.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/FT_Error_codes.vi"/>
			<Item Name="FT_Read.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/FT_Read.vi"/>
			<Item Name="FT_Write.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/FT_Write.vi"/>
			<Item Name="FPGA_Read.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/FPGA_Read.vi"/>
			<Item Name="Global.Salir Ya.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Global.Salir Ya.vi"/>
			<Item Name="MISCELANEA_WAIT.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/MISCELANEA_WAIT.vi"/>
			<Item Name="FPGA_Write.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/FPGA_Write.vi"/>
			<Item Name="info.id &amp; temp.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/info.id &amp; temp.vi"/>
			<Item Name="INFO.VER FPGA.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/INFO.VER FPGA.vi"/>
			<Item Name="WINDOWS.AUTO SIZE.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/WINDOWS.AUTO SIZE.vi"/>
			<Item Name="delay sincro.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/delay sincro.vi"/>
			<Item Name="Reset Statistics.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/Reset Statistics.vi"/>
			<Item Name="on - off channel.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/on - off channel.vi"/>
			<Item Name="Config Statistics.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/Config Statistics.vi"/>
			<Item Name="TEK_CONFIGURA ESTADISTICA Y MEDIDAS.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/TEK_CONFIGURA ESTADISTICA Y MEDIDAS.vi"/>
			<Item Name="Set trigger 50%.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/Set trigger 50%.vi"/>
			<Item Name="Set Mensajes.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/Set Mensajes.vi"/>
			<Item Name="TEK_Configura Base tiempos y Triggers.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/TEK_Configura Base tiempos y Triggers.vi"/>
			<Item Name="Set vertical position.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/Set vertical position.vi"/>
			<Item Name="TEK_Configura canales.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/TEK_Configura canales.vi"/>
			<Item Name="TEK_Configura formula Math.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/TEK_Configura formula Math.vi"/>
			<Item Name="AJUSTE V-DIV.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/AJUSTE V-DIV.vi"/>
			<Item Name="Configure osciloscopio FULL con generador.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Configure osciloscopio FULL con generador.vi"/>
			<Item Name="Barra puntos.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Barra puntos.vi"/>
			<Item Name="ADC_WRITE CONFIG.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ADC_WRITE CONFIG.vi"/>
			<Item Name="ADC_Conversion y leer.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ADC_Conversion y leer.vi"/>
			<Item Name="ASIC_READ.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_READ.vi"/>
			<Item Name="ASIC_WRITE.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_WRITE.vi"/>
			<Item Name="ASIC_WRITE_CHECK.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_WRITE_CHECK.vi"/>
			<Item Name="ASIC_Valores dac_mux_ena.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_Valores dac_mux_ena.ctl"/>
			<Item Name="ASIC_CONFIGURAR DAC MUX.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_CONFIGURAR DAC MUX.vi"/>
			<Item Name="ADC_READ VHLTHx VLLTHx.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ADC_READ VHLTHx VLLTHx.vi"/>
			<Item Name="ASIC_WRITE THX THX3 READ ADC.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_WRITE THX THX3 READ ADC.vi"/>
			<Item Name="ASIC read THx.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC read THx.vi"/>
			<Item Name="SCALER_READ VALUES.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/SCALER_READ VALUES.vi"/>
			<Item Name="SCALERS_DELAY.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/SCALERS_DELAY.vi"/>
			<Item Name="SCALERS_start windows.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/SCALERS_start windows.vi"/>
			<Item Name="Global_STOP.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Origen Socket SERVO_PCB_BUENO_v5 (muchos asics)/Global_STOP.vi"/>
			<Item Name="Rate scan.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Rate scan.vi"/>
			<Item Name="ASIC_Selecor canal Sumador (func sumas).vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_Selecor canal Sumador (func sumas).vi"/>
			<Item Name="TEK_Configura formula Math_ADDERS.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Tecktronix mdo3104/TEK_Configura formula Math_ADDERS.vi"/>
			<Item Name="Configure osciloscopio FULL con generador_ADDERS.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Configure osciloscopio FULL con generador_ADDERS.vi"/>
			<Item Name="Error Query.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Key 81160A/Error Query.vi"/>
			<Item Name="Enable Output.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Key 81160A/Enable Output.vi"/>
			<Item Name="Trigger Output.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Key 81160A/Trigger Output.vi"/>
			<Item Name="Configure Pulse Waveform.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Key 81160A/Configure Pulse Waveform.vi"/>
			<Item Name="Beep.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Key 81160A/Beep.vi"/>
			<Item Name="configure generador FULL.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/configure generador FULL.vi"/>
			<Item Name="ADC_inicialización Setup-Averaging.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ADC_inicialización Setup-Averaging.vi"/>
			<Item Name="ASIC_CONFIGURAR IABIAS.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_CONFIGURAR IABIAS.vi"/>
			<Item Name="ASIC_reset inicial.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_reset inicial.vi"/>
			<Item Name="Scalers_Escribir ventana.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Scalers_Escribir ventana.vi"/>
			<Item Name="TEST.TEMPERATURA.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST.TEMPERATURA.vi"/>
			<Item Name="Test Asic Rate Scan Adders.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Rate Scan Adders.vi"/>
			<Item Name="ASIC_Selecor canal Sumador.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_Selecor canal Sumador.vi"/>
			<Item Name="Test Asic Rate Scan.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Rate Scan.vi"/>
			<Item Name="ASIC_Valores ADD_MUX_ena.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_Valores ADD_MUX_ena.ctl"/>
			<Item Name="ASIC_CONFIGURAR add MUX.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_CONFIGURAR add MUX.vi"/>
			<Item Name="ADC_READ ADDOUT N-P.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ADC_READ ADDOUT N-P.vi"/>
			<Item Name="configure generador FULL_standalone.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/configure generador FULL_standalone.vi"/>
			<Item Name="Test Asic Analog Offset ADDERS.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Analog Offset ADDERS.vi"/>
			<Item Name="Test Asic Analog Offset.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Analog Offset.vi"/>
			<Item Name="TEST ASIC DIGITAL OFFSET GET INIT END.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST ASIC DIGITAL OFFSET GET INIT END.vi"/>
			<Item Name="TEST ASIC DIGITAL OFFSET FIND INIT END.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST ASIC DIGITAL OFFSET FIND INIT END.vi"/>
			<Item Name="SCALER_READ LVDS (neg, pos).vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/SCALER_READ LVDS (neg, pos).vi"/>
			<Item Name="ASIC_THx_FULL RANGO.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_THx_FULL RANGO.vi"/>
			<Item Name="ASIC.digital offset start-stop.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC.digital offset start-stop.ctl"/>
			<Item Name="Rate scan Find Offset.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Rate scan Find Offset.vi"/>
			<Item Name="Test Asic Digital Offset.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Digital Offset.vi"/>
			<Item Name="ADC_READ VHLTHx VLLTHx muy simple.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ADC_READ VHLTHx VLLTHx muy simple.vi"/>
			<Item Name="ASIC_WRITE THX THX3 READ ADC muy simple.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_WRITE THX THX3 READ ADC muy simple.vi"/>
			<Item Name="TEST ASIC.dac count.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/TEST ASIC.dac count.vi"/>
			<Item Name="Test Asic Max P Min N Max N Min P.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Max P Min N Max N Min P.vi"/>
			<Item Name="ASIC_CONFIGURAR SALIDAS LVDS ENA.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_CONFIGURAR SALIDAS LVDS ENA.vi"/>
			<Item Name="ASIC_CONFIGURAR SALIDAS BUF ENA.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/ASIC_CONFIGURAR SALIDAS BUF ENA.vi"/>
			<Item Name="Test Board ADC.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Board ADC.vi"/>
			<Item Name="Test Asic Register WR Default.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Register WR Default.vi"/>
			<Item Name="DP832_Read Output.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Rigol DP832/DP832_Read Output.vi"/>
			<Item Name="global_FT Handle.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/global_FT Handle.vi"/>
			<Item Name="FT_Reset_Device.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/D2XX_FT2232HL/FT_Reset_Device.vi"/>
			<Item Name="FT_Get_Status.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Get_Status.vi"/>
			<Item Name="FT_Read_Byte_Data.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Read_Byte_Data.vi"/>
			<Item Name="FT_Set_Timeouts.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Set_Timeouts.vi"/>
			<Item Name="FT_Set_Bit_Mode.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Set_Bit_Mode.vi"/>
			<Item Name="FT_Purge.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Purge.vi"/>
			<Item Name="FT_Open_Device_By_Serial_Number.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Open_Device_By_Serial_Number.vi"/>
			<Item Name="FT_Get_Device_Info_Detail.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Get_Device_Info_Detail.vi"/>
			<Item Name="FT_Get_Device_Info_List.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Get_Device_Info_List.vi"/>
			<Item Name="FT_Create_Device_Info_List.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Create_Device_Info_List.vi"/>
			<Item Name="FT_Rescan.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/D2XX_FT2232HL/FT_Rescan.vi"/>
			<Item Name="FT_Search all (state machine).ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Library VI/FT_Search all (state machine).ctl"/>
			<Item Name="FT_Search All Select description.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Library VI/FT_Search All Select description.vi"/>
			<Item Name="DP832_Enable ALL Output.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Rigol DP832/DP832_Enable ALL Output.vi"/>
			<Item Name="DP832_Configure Output.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Rigol DP832/DP832_Configure Output.vi"/>
			<Item Name="DP832_Control Behavior.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Rigol DP832/DP832_Control Behavior.ctl"/>
			<Item Name="DP832_Configure Current Limit.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Rigol DP832/DP832_Configure Current Limit.vi"/>
			<Item Name="DP832_Configure OVP.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Rigol DP832/DP832_Configure OVP.vi"/>
			<Item Name="DP832_Beep.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Rigol DP832/DP832_Beep.vi"/>
			<Item Name="DP832_Init gustavo.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Rigol DP832/DP832_Init gustavo.vi"/>
			<Item Name="Prueba_rigol.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test_Conjunto Folder/Library VI/Prueba_rigol.vi"/>
			<Item Name="file.corrige caracteres prohibidos.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/file.corrige caracteres prohibidos.vi"/>
			<Item Name="Load cluster config.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Load cluster config.vi"/>
			<Item Name="Zero cluster.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Zero cluster.vi"/>
			<Item Name="Global.exit.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Global.exit.vi"/>
			<Item Name="Save-Recall Setup.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Key 81160A/Save-Recall Setup.vi"/>
			<Item Name="Test check.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test check.ctl"/>
			<Item Name="Iconos indicador actual test.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Iconos indicador actual test.ctl"/>
			<Item Name="test check 2.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/test check 2.ctl"/>
			<Item Name="Iconos Indicador actual Test.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Iconos Indicador actual Test.vi"/>
			<Item Name="Machine State.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Machine State.ctl"/>
			<Item Name="Test Asic V1.0_2019_2.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Test Asic V1.0_2019_2.vi"/>
			<Item Name="ftd2xx.dll" Type="Document" URL="ftd2xx.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="histograma.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/histograma.vi"/>
			<Item Name="recupera_sesion_USB.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Origen Socket SERVO_PCB_BUENO_v5 (muchos asics)/recupera_sesion_USB.vi"/>
			<Item Name="bit letters.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/bit letters.vi"/>
			<Item Name="quest-about.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/quest-about.vi"/>
			<Item Name="Test Asic Rate Scan con tensiones.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Test Asic Rate Scan con tensiones.vi"/>
			<Item Name="VGA_pulso.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/VGA_pulso.vi"/>
			<Item Name="VGA_ganancia.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/VGA_ganancia.vi"/>
			<Item Name="GUI.Config Test.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/GUI.Config Test.vi"/>
			<Item Name="test.test de configuracion gui.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/test.test de configuracion gui.ctl"/>
			<Item Name="machine estate configs.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/machine estate configs.ctl"/>
			<Item Name="GUI.Comprueba limites.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/GUI.Comprueba limites.vi"/>
			<Item Name="gui.default values test.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/gui.default values test.vi"/>
			<Item Name="GUI.Config Pulse generator.vi" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/GUI.Config Pulse generator.vi"/>
			<Item Name="Machine State generador pulsos.ctl" Type="VI" URL="../../../../../Test Asic Javi_2021/Library VI/Machine State generador pulsos.ctl"/>
			<Item Name="RIGOL DP1000 Series.lvlib" Type="Library" URL="../../../../../Test Asic Javi_2021/RIGOL DP1000 Series/RIGOL DP1000 Series.lvlib"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Main Application" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{B511CD8F-BE21-4470-A7C4-3ACBADFC72C8}</Property>
				<Property Name="App_INI_GUID" Type="Str">{78EABFCD-5B97-4F87-AF3F-FF129EE73305}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{2CE40C4E-446A-4350-9E11-C85D8BAE8F13}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Main Application</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Main Application</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{09FD23A0-93D2-46A2-B12D-FA02255F97C6}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Main.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Main Application/Main.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Main Application/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{E14DB2DD-E011-49B1-8A6D-0145D8676319}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref"></Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Main Application</Property>
				<Property Name="TgtF_internalName" Type="Str">Main Application</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">Main Application</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{A9B9C488-ADD7-40F6-AAC2-547427E5CB24}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Main.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
