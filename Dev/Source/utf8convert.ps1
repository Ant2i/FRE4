$files = Get-ChildItem -Recurse | ? {Test-Path $_.FullName -PathType Leaf}

foreach($file in $files)
{
	Write-Output $file

    $content = Get-Content $file.FullName
    $content | Out-File $file.FullName -Encoding utf8
}
