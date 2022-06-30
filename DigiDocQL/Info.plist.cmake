<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>English</string>
	<key>CFBundleDisplayName</key>
	<string>DigiDocQL</string>
	<key>CFBundleExecutable</key>
	<string>DigiDocQL</string>
	<key>CFBundleIdentifier</key>
	<string>ee.ria.qdigidoc4.DigiDocQL</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string>DigiDocQL</string>
	<key>CFBundlePackageType</key>
	<string>XPC!</string>
	<key>CFBundleSupportedPlatforms</key>
	<array>
		<string>MacOSX</string>
	</array>
	<key>CFBundleShortVersionString</key>
	<string>${MACOSX_BUNDLE_SHORT_VERSION_STRING}</string>
	<key>CFBundleVersion</key>
	<string>${MACOSX_BUNDLE_BUNDLE_VERSION}</string>
	<key>NSHumanReadableCopyright</key>
	<string>${MACOSX_BUNDLE_COPYRIGHT}</string>
	<key>LSMinimumSystemVersion</key>
	<string>${CMAKE_OSX_DEPLOYMENT_TARGET}</string>
	<key>NSExtension</key>
	<dict>
		<key>NSExtensionAttributes</key>
		<dict>
			<key>QLIsDataBasedPreview</key>
			<false/>
			<key>QLSupportedContentTypes</key>
			<array>
				<string>ee.ria.bdoc</string>
				<string>ee.ria.asics</string>
			</array>
			<key>QLSupportsSearchableItems</key>
			<true/>
		</dict>
		<key>NSExtensionPointIdentifier</key>
		<string>com.apple.quicklook.preview</string>
		<key>NSExtensionPrincipalClass</key>
		<string>PreviewViewController</string>
	</dict>
</dict>
</plist>
