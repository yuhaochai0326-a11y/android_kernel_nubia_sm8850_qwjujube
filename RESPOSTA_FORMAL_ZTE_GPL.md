# RESPOSTA FORMAL À ZTE / NUBIA — RECLAMAÇÃO DE CONFORMIDADE GPL v2

**Para:** ZTE Corporation / Nubia Technology Support & Legal Compliance Department  
**Assunto:** Réplica Formal: Deficiências de Código do Kernel do RedMagic 11 Pro (NX809J), Segurança a Longo Prazo e Práticas de Obsolescência Programada  
**Dispositivo:** Nubia RedMagic 11 Pro (NX809J)  
**Processador (SoC):** Qualcomm Snapdragon 8 Elite (SM8850)  
**Contato:** idealcreativesuporte@idealcreative.com.br / @idealcreative (Telegram)  

---

## 📄 CARTA DE RÉPLICA E NOTIFICAÇÃO TÉCNICA

Agradeço o retorno e o encaminhamento desta demanda ao setor interno competente. Para que as equipes técnica e jurídica avaliem esta demanda com a devida gravidade, formalizo abaixo os pontos cruciais que motivam este chamado, amparados nas regras de conformidade de software livre, na legislação de Defesa do Consumidor e na viabilidade técnica do ciclo de vida do aparelho.

---

### 1. O Paradoxo da Segurança e a Estagnação do Kernel Linux
Atualmente, o mercado global (fortemente impulsionado por novas regulamentações europeias de ecodesign e sustentabilidade) pressiona as fabricantes de smartphones a fornecerem de 5 a 7 anos de atualizações de segurança. No entanto, na prática da engenharia de software de baixo nível, essa promessa é incompatível com a realidade de um dispositivo que possui suporte restrito e bootloader bloqueado para customização real.

O RedMagic 11 Pro foi lançado com o Kernel Linux 6.12.x (Android 16 GKI). Para manter a compatibilidade total com os drivers proprietários que vocês compilaram fora da árvore, o dispositivo ficará estagnado nesta versão de kernel para sempre. Quando o sistema operacional Android evoluir e exigir atualizações maiores de kernel (como uma futura versão LTS 7.x.x ou superior), a fabricante não realizará a migração por conta da quebra de compatibilidade com a base de drivers antiga. 

Questionamos diretamente a Engenharia da ZTE: **o que significa "segurança do dispositivo" para a empresa se, a longo prazo, o aparelho será mantido em um kernel obsoleto e o consumidor final está ativamente bloqueado de aplicar as devidas correções e atualizações de kernel por conta própria?**

---

### 2. Acordo de Garantia vs. Sequestro de Hardware
A comunidade de desenvolvedores e os consumidores avançados concordam plenamente com a perda integral da garantia do equipamento no momento em que o bootloader é desbloqueado. Essa é uma regra de mercado aceitável para mitigar riscos de suporte técnico. O que não concordamos é sermos feitos de reféns do equipamento após a compra.

Ao reter a capacidade de desbloqueio completo do ecossistema de software e limitar o suporte a um curto período de atualizações oficiais, a empresa fere o **Direito ao Reparo (Right to Repair)** e o direito fundamental de propriedade. O consumidor é impedido de reaproveitar o hardware (que possui um processador Snapdragon 8 Elite de altíssimo desempenho) para outros fins após o fim da vida útil oficial do smartphone — como a instalação de distribuições Linux genéricas ou servidores residenciais. Isso frustra o cliente e gera, inevitavelmente, lixo eletrônico (*e-waste*) de forma prematura e irresponsável.

---

### 3. Obsolescência Programada e a Legislação Brasileira (Código de Defesa do Consumidor - CDC)
No Brasil, o **Superior Tribunal de Justiça (STJ)** já pacificou o entendimento de que a durabilidade de um produto de consumo durável deve corresponder à sua "vida útil esperada", e não apenas ao período de garantia contratual ou de suporte comercial primário oferecido pela fabricante. 

Tornar um hardware de altíssimo valor e desempenho obsoleto, vulnerável e virtualmente descartável por falta de manutenção de software configura prática abusiva (violando o **Artigo 39 do Código de Defesa do Consumidor - CDC**) e caracteriza uma clara estratégia de **obsolescência programada**. A liberação do código-fonte completo é a única ferramenta que permite à sociedade civil manter o aparelho seguro e funcional após o encerramento do suporte oficial da marca.

---

### 4. Conformidade GPLv2: O Mínimo Compilável e Funcional (Causa Raiz do Boot Hang)
O pilar técnico desta reclamação é a liberação de um código-fonte de kernel incompleto e disfuncional. Estabelecemos aqui um limite claro de propriedade intelectual: **em momento algum solicitamos acesso a segredos comerciais ou industriais da ZTE.** 

Não demandamos os algoritmos proprietários de processamento de imagem das câmeras, tecnologias de calibração fina de tela ou os firmwares fechados e criptografados da banda base do modem celular. A ZTE e seus parceiros de hardware têm todo o direito legal de manter esses elementos sob segredo comercial.

No entanto, a nossa exigência técnica — **amparada inegociavelmente pela licença global GPLv2 do Kernel Linux** — é a disponibilização das partes estruturais e configurações de compilação necessárias para que o kernel seja minimamente compilável e capaz de inicializar (boot) o smartphone de forma funcional.

#### O Nosso Blocker Atual de Inicialização (Evidência de Inconformidade):
Durante os testes de compilação com a árvore fornecida pela ZTE, o kernel compila mas trava indefinidamente na tela do logotipo inicial da RedMagic. O log de console (`console-ramoops`) aponta o seguinte erro impeditivo:
```
[0.181496] arm-scmi arm-scmi.1.auto: Failed to get FC for protocol 13 [MSG_ID:6 / RES_ID:0] - ret:-22
...
[1.112952] arm-scmi arm-scmi.1.auto: timed out in resp (caller: do_xfer+0x140/0x4ec)
[1.116211] scmi_cpuss_telemetry_probe: Not able to find shared memory location
```
Este **timeout no protocolo SCMI** ocorre porque a ZTE omitiu o fragmento de configuração da plataforma (`canoe.fragment`) e as implementações internas do driver de mailbox/SCMI. Como consequência deste travamento:
1. O subsistema `remoteproc` falha ao carregar os coprocessadores (`adsp-loader: fail to get rproc`).
2. O driver de segurança `keymint` não inicializa.
3. O daemon de volumes `vold` não consegue descriptografar a partição `/data` (criptografada por FBE - *File-Based Encryption*).
4. O sistema operacional congela no boot do logotipo por falta de montagem da partição userdata.

#### O Mínimo Funcional Exigido por Lei (GPLv2):
Para que o código fornecido esteja em conformidade com a GPLv2, a ZTE deve fornecer os fontes (e não stubs vazios ou blobs fechados) dos seguintes componentes integrados ao espaço de kernel (*kernel-space*):
*   **Camada de Inicialização e SCMI:** A configuração de mailbox da CPU (`canoe.fragment` e DTBs de coordenação com o firmware `PDP0`) para evitar o timeout de boot.
*   **Driver do Painel de Toque (Touchscreen):** O código original C do driver do touchscreen (`zte_tpd`) para que a tela aceite toques.
*   **Políticas de Energia e Carga:** Os drivers de gerenciamento de bateria e carga (`zte_charger_policy` e `zte_power_supply`) essenciais para que o dispositivo ligue e carregue de forma segura.
*   **Drivers Básicos de Display e Codec de Áudio:** O suporte mínimo para inicializar o console de tela e reproduzir sons básicos de notificação do sistema.

**Os firmwares da câmera, modem celular e outros chips secundários podem permanecer fechados em nível de firmware (binários carregados na RAM do chip) ou em nível de HAL (User-Space), desde que o kernel Linux fornecido seja capaz de bootar o Android e acessar a tela principal de forma autônoma.**

---

## 🎯 CONCLUSÃO E SOLICITAÇÃO

Solicitamos que a assessoria jurídica e a equipe de engenharia de software da ZTE / Nubia:
1. Providenciem a liberação de um pacote de código-fonte de kernel atualizado e em conformidade com a GPLv2, contendo as mailboxes de inicialização, drivers de tela/toque, gerenciador de carregamento e o defconfig completo de hardware.
2. Repensem a política de retenção que transforma aparelhos funcionais de alta performance em lixo eletrônico após o encerramento do suporte de atualizações OTA.

A comunidade de desenvolvimento está disposta a colaborar e reportar correções, mas dependemos de uma base de código minimamente compilável e funcional, em total consonância com a licença que rege o próprio Kernel Linux.

Aguardo um retorno técnico adequado, transparente e em tempo oportuno.

Atenciosamente,  
**Coding-BR / Ideal Creative**  
*Contato: idealcreativesuporte@idealcreative.com.br*
