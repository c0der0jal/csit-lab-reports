<#
.SYNOPSIS
    Deploy ASP.NET Core app to Azure App Service

.DESCRIPTION
    Simple deployment script for demonstration purposes.
    Prerequisites: Azure CLI installed and logged in (az login)

.EXAMPLE
    .\deploy-azure.ps1 -ResourceGroup "my-rg" -AppName "my-webapp" -Location "eastus"
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$ResourceGroup,
    
    [Parameter(Mandatory=$true)]
    [string]$AppName,
    
    [Parameter(Mandatory=$true)]
    [string]$Location = "eastus",
    
    [string]$ProjectPath = ".\AzureProject.csproj",
    
    [string]$PublishFolder = ".\publish"
)

# Build and publish
Write-Host "Building and publishing..." -ForegroundColor Cyan
dotnet publish $ProjectPath -c Release -o $PublishFolder

if ($LASTEXITCODE -ne 0) {
    Write-Error "Publish failed"
    exit 1
}

# Create resource group if not exists
Write-Host "Creating resource group..." -ForegroundColor Cyan
az group create --name $ResourceGroup --location $Location | Out-Null

# Create App Service plan (Free tier for demo)
Write-Host "Creating App Service plan..." -ForegroundColor Cyan
az appservice plan create `
    --name "${AppName}-plan" `
    --resource-group $ResourceGroup `
    --location $Location `
    --sku F1 `
    --is-linux `
    | Out-Null

# Create Web App
Write-Host "Creating Web App..." -ForegroundColor Cyan
az webapp create `
    --name $AppName `
    --resource-group $ResourceGroup `
    --plan "${AppName}-plan" `
    --runtime "DOTNET|10.0" `
    | Out-Null

# Deploy via zip
Write-Host "Deploying to Azure..." -ForegroundColor Cyan
Compress-Archive -Path "$PublishFolder\*" -DestinationPath "deploy.zip" -Force
az webapp deploy `
    --name $AppName `
    --resource-group $ResourceGroup `
    --src-path "deploy.zip" `
    --type zip `
    | Out-Null

# Cleanup
Remove-Item "deploy.zip" -Force -ErrorAction SilentlyContinue
Remove-Item $PublishFolder -Recurse -Force -ErrorAction SilentlyContinue

Write-Host "Deployment complete! URL: https://$AppName.azurewebsites.net" -ForegroundColor Green