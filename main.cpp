import asyncio
import aiohttp
import time

async def check_platform(session, platform_name, url):
    try:
        async with session.get(url, timeout=5) as response:
            if response.status == 200:
                print(f"[+] Found: {platform_name} -> {url}")
                return platform_name, url
    except:
        pass
    return None

async def main():
    print("--- Digital Footprint Identifier v4.0.5 ---")
    username = input("[?] Enter target username to audit: ")
    
    # Mock platform list
    platforms = {
        "GitHub": f"https://github.com/{username}",
        "Twitter": f"https://twitter.com/{username}",
        "Instagram": f"https://instagram.com/{username}",
    }

    print(f"[*] Commencing audit for node: '{username}'...")
    
    async with aiohttp.ClientSession() as session:
        tasks = [check_platform(session, name, url) for name, url in platforms.items()]
        results = await asyncio.gather(*tasks)
        
    found = [r for r in results if r]
    print(f"\n[!] Audit Complete. Nodes identified: {len(found)}")

if __name__ == "__main__":
    asyncio.run(main())
