#include <iostream>
#include <Windows.h>
#include <Wincrypt.h>
#include <vector>
#include <string>
#include <sstream>

enum HashType
{
	HashSha1, HashMd5, HashSha256
};

std::string GetHashText(const void* data, const size_t data_size, HashType hashType)
{
	HCRYPTPROV hProv = NULL;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
		return "";
	}

	BOOL hash_ok = FALSE;
	HCRYPTPROV hHash = NULL;
	switch (hashType) {
	case HashSha1: hash_ok = CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash); break;
	case HashMd5: hash_ok = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash); break;
	case HashSha256: hash_ok = CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash); break;
	}

	if (!hash_ok) {
		CryptReleaseContext(hProv, 0);
		return "";
	}

	if (!CryptHashData(hHash, static_cast<const BYTE*>(data), data_size, 0)) {
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	DWORD cbHashSize = 0, dwCount = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&cbHashSize, &dwCount, 0)) {
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	std::vector<BYTE> buffer(cbHashSize);
	if (!CryptGetHashParam(hHash, HP_HASHVAL, reinterpret_cast<BYTE*>(&buffer[0]), &cbHashSize, 0)) {
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	std::ostringstream oss;

	for (std::vector<BYTE>::const_iterator iter = buffer.begin(); iter != buffer.end(); ++iter) {
		oss.fill('0');
		oss.width(2);
		oss << std::hex << static_cast<const int>(*iter);
	}
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	return oss.str();
}

bool resultFinished(const std::string& str) {
	if (str.size() < 8)
		return false;
	for (char c : str)
	{
		if (c == '_')
			return false;
	}
	return true;
}

int main()
{
	std::cout << "which part ? (1 or 2)\n";
	int part = 1;
	std::cin >> part;
	std::string input = "wtnhxymk";
	long digit = 0;
	std::string result;
	std::string hashResult = "init";
	std::string composed;
	std::string goal = "00000";
	std::string::size_type idx = 0;
	int size = 5;
	if (part != 1)
		result = "________";
	while (!resultFinished(result)) {
		while (hashResult.substr(0, size) != goal) {
			composed = input + std::to_string(digit++);
			hashResult = GetHashText(composed.c_str(), composed.size(), HashMd5);
		}
		if (part == 1)
			result += hashResult[5];
		else {
			idx = hashResult[5] - '0';
			if (idx < 8 && result[idx] == '_')
				result[idx] = hashResult[6];
		}
		std::cout << "md5 code : " << hashResult << " | result build : " << result << " | loop : " << digit << std::endl;
		composed = input + std::to_string(digit++);
		hashResult = GetHashText(composed.c_str(), composed.size(), HashMd5);
	}
	std::cout << "found : " << result << std::endl;
	return 0;

}