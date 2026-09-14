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
		<Item Name="Main.vi" Type="VI" URL="../Main.vi"/>
		<Item Name="SHARED VI&apos;S.lvlib" Type="Library" URL="../../SHARED VI&apos;S/SHARED VI&apos;S.lvlib"/>
		<Item Name="CheckValues_config_estacionXML.vi" Type="VI" URL="../../SHARED VI&apos;S/CheckValues_config_estacionXML.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="VISA Find Search Mode.ctl" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Find Search Mode.ctl"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="subTimeDelay.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/TimeDelayBlock.llb/subTimeDelay.vi"/>
				<Item Name="subDisplayMessage.vi" Type="VI" URL="/&lt;vilib&gt;/express/express output/DisplayMessageBlock.llb/subDisplayMessage.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
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
				<Item Name="Read From XML File(array).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File(array).vi"/>
				<Item Name="Read From XML File(string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File(string).vi"/>
				<Item Name="Read From XML File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File.vi"/>
				<Item Name="Write to XML File(string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Write to XML File(string).vi"/>
				<Item Name="Write to XML File(array).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Write to XML File(array).vi"/>
				<Item Name="Write to XML File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Write to XML File.vi"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
			</Item>
			<Item Name="MAIN_call.vi" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/MAIN_call.vi"/>
			<Item Name="Distancia_Z.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Distancia_Z.ctl"/>
			<Item Name="Distancia.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Distancia.ctl"/>
			<Item Name="Tipo_movimiento.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Tipo_movimiento.ctl"/>
			<Item Name="ESTADOS.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/ESTADOS.ctl"/>
			<Item Name="Cluster_tracking.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Cluster_tracking.ctl"/>
			<Item Name="Cluster_refs_controles.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Cluster_refs_controles.ctl"/>
			<Item Name="SHARED TYPES.lvlib" Type="Library" URL="../../SHARED TYPES/SHARED TYPES.lvlib"/>
			<Item Name="Comandos.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Comandos.ctl"/>
			<Item Name="Estados_arduino.ctl" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/Typedefs/Estados_arduino.ctl"/>
			<Item Name="Check_limits.vi" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/Check_limits.vi"/>
			<Item Name="Enviar_comando.vi" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/Enviar_comando.vi"/>
			<Item Name="Ack_comando_arduino.vi" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/Ack_comando_arduino.vi"/>
			<Item Name="Enviar_trama_movimiento.vi" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/Enviar_trama_movimiento.vi"/>
			<Item Name="check_finalMovimiento.vi" Type="VI" URL="../../LVPROJ_MOVIMIENTO_CABEZAL/LABVIEW_MOVIMIENTO/MOVIMIENTO CABEZAL/VI&apos;s/check_finalMovimiento.vi"/>
			<Item Name="Array_deClusterBandeja.ctl" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/Type_defs/Array_deClusterBandeja.ctl"/>
			<Item Name="bandejasXML_to_ArrayClusters.vi" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/VI&apos;S/bandejasXML_to_ArrayClusters.vi"/>
			<Item Name="ActivarDatosBandeja.vi" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/VI&apos;S/ActivarDatosBandeja.vi"/>
			<Item Name="CREAR_BANDEJA_xml.vi" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/VI&apos;S/CREAR_BANDEJA_xml.vi"/>
			<Item Name="DesactivarDatosBandeja.vi" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/VI&apos;S/DesactivarDatosBandeja.vi"/>
			<Item Name="ESTADOS_CREAR_BANDEJA.ctl" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/Type_defs/ESTADOS_CREAR_BANDEJA.ctl"/>
			<Item Name="MAIN_CREAR_BANDEJA.vi" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/MAIN_CREAR_BANDEJA.vi"/>
			<Item Name="TAREAS_ROBOT.ctl" Type="VI" URL="../../LABVIEW_ROBOT_MASTER/Type_defs/TAREAS_ROBOT.ctl"/>
			<Item Name="Data_Bandeja.ctl" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/Type_defs/Data_Bandeja.ctl"/>
			<Item Name="Refs_controles_input_Bandeja.ctl" Type="VI" URL="../../LVPROJ_CREAR BANDEJAS/Type_defs/Refs_controles_input_Bandeja.ctl"/>
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
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Main.vi</Property>
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
