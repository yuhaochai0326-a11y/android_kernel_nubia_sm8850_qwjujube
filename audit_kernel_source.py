import os
import re
import sys

def audit_driver(name, path):
    print(f"--- Auditando: {name} ({path}) ---")
    if not os.path.exists(path):
        print(f"❌ Erro: Caminho não existe: {path}")
        return

    kbuild_files = []
    for root, dirs, files in os.walk(path):
        for f in files:
            if f in ['Kbuild', 'Makefile']:
                kbuild_files.append(os.path.join(root, f))

    if not kbuild_files:
        print(f"⚠️ Aviso: Nenhum Kbuild/Makefile encontrado em {path}")
        return

    missing_files = []
    found_files = 0
    
    for kb in kbuild_files:
        with open(kb, 'r', errors='ignore') as f:
            content = f.read()
            
        # Busca por padrões de objetos .o
        # Captura: obj-y += file.o ou module-y := file.o ou ./path/file.o
        objs = re.findall(r'([a-zA-Z0-9_/.-]+\.o)\b', content)
        
        kb_dir = os.path.dirname(kb)
        
        for obj in objs:
            # Ignora o próprio módulo composto se ele for o target principal
            # (Geralmente obj-m += modulo.o)
            source_c = obj.replace('.o', '.c')
            source_s = obj.replace('.o', '.S')
            
            # Tenta resolver o caminho
            potential_paths = [
                os.path.abspath(os.path.join(kb_dir, source_c)),
                os.path.abspath(os.path.join(kb_dir, source_s))
            ]
            
            # Se começar com ./ ou for apenas o nome, o compilador busca no dir do Kbuild
            exists = False
            for p in potential_paths:
                if os.path.exists(p):
                    exists = True
                    break
            
            # Se for um módulo composto (ex: msm_kgsl.o), ele não tem um msm_kgsl.c 
            # mas sim uma lista de dependências. Vamos ignorar se for o nome do diretório ou 
            # se tiver sub-objetos definidos no mesmo Kbuild.
            mod_name = obj.replace('.o', '')
            if not exists:
                if f"{mod_name}-y" in content or f"{mod_name}-objs" in content:
                    continue
                
                # Se ainda não achou, é um erro real de arquivo fonte
                missing_files.append(f"{kb}: {obj} (buscou em {kb_dir})")
            else:
                found_files += 1

    unique_missing = list(set(missing_files))
    if not unique_missing:
        print(f"✅ Sucesso: {found_files} arquivos fonte verificados e presentes.")
    else:
        print(f"❌ FALTANDO: {len(unique_missing)} arquivos:")
        for m in unique_missing[:20]:
            print(f"   - {m}")
        if len(unique_missing) > 20:
            print(f"   ... e mais {len(unique_missing)-20} arquivos.")
    print("\n")

# Lista de componentes para auditoria
root_dir = "/home/adrianojr59/kernel_build"
components = {
    "GPU": "vendor/qcom/opensource/graphics-kernel",
    "Display": "vendor/qcom/opensource/display-drivers",
    "Camera": "vendor/qcom/opensource/camera-kernel",
    "Audio": "vendor/qcom/opensource/audio-kernel",
    "Video": "vendor/qcom/opensource/video-driver",
    "Touch": "vendor/qcom/opensource/touch-drivers",
    "BT": "vendor/qcom/opensource/bt-kernel",
    "WLAN": "vendor/qcom/opensource/wlan",
    "DataIPA": "vendor/qcom/opensource/dataipa",
    "SecureMSM": "vendor/qcom/opensource/securemsm-kernel",
    "MM-Drivers": "vendor/qcom/opensource/mm-drivers"
}

for name, rel_path in components.items():
    audit_driver(name, os.path.join(root_dir, rel_path))
