# Azure App Service Deployment

Simple ASP.NET Core MVC app deployment to Azure.

## Prerequisites
- [Azure CLI](https://learn.microsoft.com/cli/azure/install-azure-cli)
- .NET 10.0 SDK
- Azure subscription

## Quick Deploy

```powershell
# 1. Login to Azure
az login

# 2. Run deployment script
.\deploy-azure.ps1 -ResourceGroup "my-rg" -AppName "my-webapp" -Location "eastus"
```

## What the script does
1. Builds & publishes the app (`dotnet publish -c Release`)
2. Creates Resource Group
3. Creates App Service Plan (Free tier F1)
4. Creates Linux Web App with .NET 10.0
5. Deploys via ZIP deploy
6. Outputs the public URL

## Manual Steps (Alternative)

```bash
# Publish locally
dotnet publish AzureProject.csproj -c Release -o ./publish

# Create resources
az group create -n my-rg -l eastus
az appservice plan create -n my-webapp-plan -g my-rg --sku F1 --is-linux
az webapp create -n my-webapp -g my-rg -p my-webapp-plan --runtime "DOTNET|10.0"

# Deploy
cd publish && zip -r ../deploy.zip . && cd ..
az webapp deploy -n my-webapp -g my-rg --src-path deploy.zip --type zip
```

## Verify Deployment
Visit: `https://<your-app-name>.azurewebsites.net`

## Cleanup
```bash
az group delete -n my-rg --yes --no-wait
```